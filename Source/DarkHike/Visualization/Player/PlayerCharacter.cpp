// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Instantiating your class Components
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));

    // Set the location and rotation of the Character Mesh Transform
    if (GetMesh() != nullptr)
    {
        GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));
    }

    // Disable the camera rotation with mesh
    bUseControllerRotationYaw = false;

    // Attaching your class Components to the default character's Skeletal Mesh Component.
    SpringArmComp->SetupAttachment(RootComponent);
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    InteractionBox->SetupAttachment(RootComponent);

    // Setting class variables of the spring arm and camera
    SpringArmComp->TargetArmLength = 3000.f;
    SpringArmComp->AddWorldRotation(FRotator(-45.f, 135.f, 0.f));
    SpringArmComp->bDoCollisionTest = false;
    SpringArmComp->bInheritYaw = false;
    SpringArmComp->bEnableCameraLag = true;
    SpringArmComp->CameraLagSpeed = 3.f;
    SpringArmComp->CameraLagMaxDistance = 100.f;
    CameraComp->FieldOfView = 50.f;

    // Setting class variables of the interaction collider
    InteractionBox->SetBoxExtent(FVector(InteractionDistance, InteractionDistance, 100.f));
    InteractionBox->SetCollisionProfileName(TEXT("PlayerInteract"));

    // Setting class variables of the Character movement component
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bCanWalkOffLedges = false;
    GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

    bIsPaused = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

    // Set the control rotation to match the isometric view
    Controller->SetControlRotation(FRotator(0.f, 135.f, 0.f));
	
    // If FadeInAtStart is true, the screen fades from black to regular on start of the level
    if (FadeInAtStart)
    {
        StartFadeIn(FadeInAtStartDuration);
    }
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Possible performance problem
    // If problem, use overlaps
    CheckOverlappingInteractables();

    if (GetCharacterMovement()->IsFalling())
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Is falling"));
    }
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::BeginSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::EndSprint);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::OnInteract);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("RawAxisValue: %f"), AxisValue));
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("AbsAxisValue: %f"), FMath::Abs(AxisValue)));
    
    if ((Controller != nullptr) && (AxisValue != 0.0f) && (FMath::Abs(AxisValue) >= 0.1f))
    {
        // Find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, AxisValue);
    }
}

void APlayerCharacter::MoveRight(float AxisValue)
{
    if ((Controller != nullptr) && (AxisValue != 0.0f) && (FMath::Abs(AxisValue) >= 0.1f))
    {
        // Find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get right vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Add movement in that direction
        AddMovementInput(Direction, AxisValue);
    }
}

void APlayerCharacter::BeginSprint()
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::EndSprint()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::OnInteract()
{
    //GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here"));
    if (Interface && Interface->CheckInteraction() && !bIsPaused)
    {
        Interface->InteractWithMe();
    }
}

void APlayerCharacter::CheckOverlappingInteractables()
{
    TArray<AActor*>OverlappingActors;

    // Getting all overlapping actors with Interactable interface
    // Collision preset set to fetch only Interactables
    InteractionBox->GetOverlappingActors(OverlappingActors);

    //Getting the closest ovelapping interactable actor
    if (OverlappingActors.Num() == 0)
    {
        // Just to be safe, hide any active interaction widgets
        if (Interface)
        {
            Interface->HideInteractionWidget();
            Interface = nullptr;
            ClosestActor = nullptr;
        }
        return;
    }

    ClosestActor = OverlappingActors[0];

    for (auto CurrentActor : OverlappingActors)
    {
        if (GetDistanceTo(CurrentActor) < GetDistanceTo(ClosestActor))
        {
            ClosestActor = CurrentActor;
        }
    }

    // If there's already an interaction widget active, hide it
    if (Interface)
    {
        Interface->HideInteractionWidget();
    }

    Interface = Cast<IInteractableInterface>(ClosestActor);

    // !!!!The colliders of the interactables can't overlap each other,
    // because now the function just checks the closest one!!!
    // 
    // Show only the interaction widget of the closest interactable
    if (Interface && Interface->CheckInteraction())
    {
        Interface->ShowInteractionWidget();
    }
}

// Starts the fade in from black
void APlayerCharacter::StartFadeIn(float FadeTime)
{
    // Call UGameplayStatics::GetPlayerController to get the player controller
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (PlayerController)
    {
        // Call UGameplayStatics::GetPlayerCameraManager to get the camera manager
        APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

        if (CameraManager)
        {
            // Call APlayerCameraManager::StartCameraFade to initiate the fade-in effect
            CameraManager->StartCameraFade(1.0f, 0.0f, FadeTime, FLinearColor::Black, false, false);
        }
    }
}

// Starts the fade out to black
void APlayerCharacter::StartFadeOut(float FadeTime)
{
    // Call UGameplayStatics::GetPlayerController to get the player controller
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (PlayerController)
    {
        // Call UGameplayStatics::GetPlayerCameraManager to get the camera manager
        APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

        if (CameraManager)
        {
            // Call APlayerCameraManager::StartCameraFade to initiate the fade-in effect
            CameraManager->StartCameraFade(0.0f, 1.0f, FadeTime, FLinearColor::Black, false, true);
        }
    }
}

// Enables player movement
void APlayerCharacter::EnableMovement()
{
    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

// Disables player movement
void APlayerCharacter::DisableMovement()
{
    GetCharacterMovement()->DisableMovement();
}

void APlayerCharacter::SetFocusOnOptionWidget(UButton* WidgetToFocus)
{
    if (WidgetToFocus)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (PlayerController)
        {
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(WidgetToFocus->TakeWidget());
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
            PlayerController->SetInputMode(InputMode);
            PlayerController->bShowMouseCursor = false;
        }
    }
}