// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/BoxComponent.h"
#include "../Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiating and setting your class Components
	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionProfileName(TEXT("Interactable"));

	KeyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	KeyItemMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	InteractionWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget->SetVisibility(false);
	RotateWidgetToCamera();
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AInteractableObject::CheckInteraction()
{
	return bInteractionEnabled;
}

void AInteractableObject::InteractWithMe()
{
	//HERE THE CHECK FOR THE KEY ITEM**********
	
	PlayAnimation();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Interact succeeded!"));
}

void AInteractableObject::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void AInteractableObject::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void AInteractableObject::PlayAnimation()
{
}

void AInteractableObject::RotateWidgetToCamera()
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

/* Old Widget Rotation
void AInteractableObject::RotateWidgetToCamera()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	APlayerCharacter* PlayerInstance = nullptr;

	if (PlayerController)
	{
		// Get the character controlled by the player controller
		PlayerInstance = Cast<APlayerCharacter>(PlayerController->GetPawn());
	}

	if (PlayerInstance && PlayerInstance->CameraComp && InteractionWidget)
	{
		// Get component locations
		FVector WidgetLocation = InteractionWidget->GetComponentLocation();

		// Calculate the direction from the widget to the camera
		FVector CameraToWidgetDirection = WidgetLocation - PlayerInstance->CameraComp->GetComponentLocation();
		CameraToWidgetDirection.Normalize();

		// Calculate the rotation that makes the widget face the camera
		FRotator WidgetRotation = CameraToWidgetDirection.Rotation();

		// Adjust the widget rotation to set the desired roll angle
		WidgetRotation.Pitch = 45.0f;
		WidgetRotation.Yaw = -40.f;

		// Set the widget's rotation
		InteractionWidget->SetWorldRotation(WidgetRotation);
	}
}*/