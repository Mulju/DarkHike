// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamb.h"
#include <Kismet/GameplayStatics.h>
#include "Components/BoxComponent.h"
#include "../Visualization/Interactables/Objects/Altar.h"

// Sets default values
ALamb::ALamb()
{
 	// Init Inherited Settings
	PrimaryActorTick.bCanEverTick = true;

	//Create Collider offset and setup Component Refs
	ColliderMatchPivot = CreateDefaultSubobject<USceneComponent>("Collider Match Pivot");
	DefaultCapsuleComponent = ACharacter::GetCapsuleComponent();
	DefaultCapsuleComponent->InitCapsuleSize(20.0f, 20.0f);
	DefaultSkeletalMeshComponent = ACharacter::GetMesh();
	
	#if WITH_EDITORONLY_DATA
	DefaultArrow = ACharacter::GetArrowComponent();
	#endif

	ColliderMatchPivot->SetupAttachment(DefaultCapsuleComponent);
	DefaultSkeletalMeshComponent->SetupAttachment(ColliderMatchPivot);
	
	#if WITH_EDITORONLY_DATA
	DefaultArrow->SetupAttachment(ColliderMatchPivot);
	#endif

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionProfileName(TEXT("Interactable"));

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	InteractionWidget->SetupAttachment(RootComponent);

	//Init variables
	PlayerActor = nullptr;
	LambName = "Basic Lamb";
	bClearReached = false;
	bToSacrifice = false;
	WalkSpeed = 67;
	TrotSpeed = 186;
	RunSpeed = 300;
	ClearZone = nullptr;
	SacrificeZone = nullptr;
	WaitZone = nullptr;

	DialogueWidgetInstance = nullptr;
	DialogueIndex = -1;
	DialoguesIndex = 0;
	PlayerInstance = nullptr;

}

// Called when the game starts or when spawned
void ALamb::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = Cast<AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
	if (PlayerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerActor Name: %s"), *PlayerActor->GetName());
	}

	CalculateColliderSize();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (DialogueWidget)
	{
		if (!DialogueWidgetInstance)
		{
			DialogueWidgetInstance = CreateWidget<UDialogueWidget>(PlayerController, DialogueWidget);
		}
	}

	InteractionWidget->SetVisibility(false);
	GetPlayerCharacter();
	RotateWidgetToCamera();

}

// Called every frame
void ALamb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerActor)
	{
		DistancePlayer = FVector::Distance( GetActorLocation(), PlayerActor->GetActorLocation() );
	}

	RotateWidgetToCamera();
}

bool ALamb::CheckInteraction()
{
	return bInteractionEnabled;
}

void ALamb::InteractWithMe()
{
	// Activating the maiden option of the altar
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAltar::StaticClass(), FoundActors);

	//FString DebugMessage = FString::Printf(TEXT("Found %d actors."), FoundActors.Num());
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);

	/*
	if (FoundActors.Num() == 1)
	{
		AAltar* AltarInstance = Cast<AAltar>(FoundActors[0]);

		if (AltarInstance)
		{
			AltarInstance->bIsLambActivated = true;
		}
	}*/

	ShowDialogue();
}

void ALamb::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void ALamb::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void ALamb::ShowDialogue()
{
	if (DialogueWidgetInstance && PlayerInstance && Dialogues.Num() > 0)
	{
		DialogueIndex++;

		PlayerInstance->DisableMovement();

		if (DialogueIndex >= 0 && DialogueIndex < Dialogues[DialoguesIndex].DialogueList.Num())
		{
			DialogueWidgetInstance->AddToViewport();

			FString DialogueText = Dialogues[DialoguesIndex].DialogueList[DialogueIndex];

			if (DialogueWidgetInstance)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here"));
				DialogueWidgetInstance->SetDialogueText(DialogueText);
			}
		}
		else
		{
			DialogueWidgetInstance->RemoveFromViewport();
			DialogueIndex = -1;
			PlayerInstance->EnableMovement();
		}
	}
}

void ALamb::RotateWidgetToCamera()
{
	if (InteractionWidget)
	{
		FRotator WidgetRotation;

		// Adjust the widget rotation to set the desired roll angle
		WidgetRotation.Pitch = 45.0f;
		WidgetRotation.Yaw = -40.f;
		WidgetRotation.Roll = 2.5f;

		// Set the widget's rotation
		InteractionWidget->SetWorldRotation(WidgetRotation);
	}
}

void ALamb::IncreaseDialoguesIndex()
{
	if (Dialogues.Num() > 0 && (DialoguesIndex + 1) < Dialogues.Num())
	{
		DialoguesIndex++;
	}
}

void ALamb::CalculateColliderSize()
{
	FBoxSphereBounds Bounds = DefaultSkeletalMeshComponent->GetSkeletalMeshAsset()->GetBounds();
	FVector BoxExtent = Bounds.GetBox().GetExtent();
	UE_LOG(LogTemp, Warning, TEXT("Box Extent: %s"), *BoxExtent.ToString());

	DefaultCapsuleComponent->SetCapsuleRadius(BoxExtent.X);
	DefaultCapsuleComponent->SetCapsuleHalfHeight(BoxExtent.Z);

	ColliderMatchPivot->AddWorldOffset((BoxExtent.Z * BoxExtent.DownVector));

}

void ALamb::GetPlayerCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		// Get the character controlled by the player controller
		PlayerInstance = Cast<APlayerCharacter>(PlayerController->GetPawn());
	}
}


