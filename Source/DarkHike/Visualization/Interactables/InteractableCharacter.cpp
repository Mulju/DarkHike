// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableCharacter.h"
#include "Components/BoxComponent.h"
#include "../UI/DialogueWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

// Sets default values
AInteractableCharacter::AInteractableCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiating and setting your class Components
	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionProfileName(TEXT("Interactable"));

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	CharacterMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	InteractionWidget->SetupAttachment(RootComponent);

	DialogueWidgetInstance = nullptr;

	DialogueIndex = -1;
	DialoguesIndex = 0;

	PlayerInstance = nullptr;
}

// Called when the game starts or when spawned
void AInteractableCharacter::BeginPlay()
{
	Super::BeginPlay();

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
void AInteractableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AInteractableCharacter::CheckInteraction()
{
	return bInteractionEnabled;
}

void AInteractableCharacter::InteractWithMe()
{
	ShowDialogue();
}

void AInteractableCharacter::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void AInteractableCharacter::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void AInteractableCharacter::PlayAnimation()
{
}

void AInteractableCharacter::ShowDialogue()
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
	OnCharacterInteractionEvent.Broadcast();
}

// Gets reference to the player character
void AInteractableCharacter::GetPlayerCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		// Get the character controlled by the player controller
		PlayerInstance = Cast<APlayerCharacter>(PlayerController->GetPawn());
	}
}

// Rotate widget to camera
void AInteractableCharacter::RotateWidgetToCamera()
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

void AInteractableCharacter::IncreaseDialoguesIndex()
{
	if (Dialogues.Num() > 0 && (DialoguesIndex + 1) < Dialogues.Num())
	{
		DialoguesIndex++;
	}
}

int AInteractableCharacter::GetDialogueArrayLength(int InputDialogueIndex)
{
	if(InputDialogueIndex <= Dialogues.Num()-1 && InputDialogueIndex>-1)
	{
	int Length = Dialogues[InputDialogueIndex].DialogueList.Num();

	return Length;
	}
	else
	{
		//Print error
		return -1;
	}
}

USkeletalMeshComponent* AInteractableCharacter::GetSkeletalMesh()
{
	return CharacterMesh;
}

/* Old Rotate widget to camera
void AInteractableCharacter::RotateWidgetToCamera()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerInstance = nullptr;

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