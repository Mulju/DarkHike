// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"
#include "Components/BoxComponent.h"
#include "../Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values
AKeyItem::AKeyItem()
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
void AKeyItem::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionWidget->SetVisibility(false);
	RotateWidgetToCamera();
}

// Called every frame
void AKeyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AKeyItem::CheckInteraction()
{
	return bInteractionEnabled;
}

void AKeyItem::InteractWithMe()
{
	/*
	AddToInventory();
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Destroyed the object!"));
	*/
}

void AKeyItem::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void AKeyItem::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void AKeyItem::AddToInventory()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Key item added to the inventory!"));
}

void AKeyItem::RotateWidgetToCamera()
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
void AKeyItem::RotateWidgetToCamera()
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