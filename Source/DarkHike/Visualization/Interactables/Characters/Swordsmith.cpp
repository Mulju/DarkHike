// Fill out your copyright notice in the Description page of Project Settings.


#include "Swordsmith.h"
#include "../InteractableCharacter.h"
#include "../../UI/DialogueWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/BoxComponent.h"
#include "../Objects/Altar.h"

void ASwordsmith::BeginPlay()
{
	Super::BeginPlay();

	DelayDelegate.BindLambda([&]()
		{
			DialogueWidgetInstance->AddToViewport();

			FString DialogueText = Dialogues[DialoguesIndex].DialogueList[DialogueIndex];

			if (DialogueWidgetInstance)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here"));
				DialogueWidgetInstance->SetDialogueText(DialogueText);
			}
		});

	NormalMaterial = PlayerInstance->GetMesh()->GetMaterial(3);
}

void ASwordsmith::InteractWithMe()
{
	ShowDialogue();
}

void ASwordsmith::ShowDialogue()
{
	if (DialogueWidgetInstance && PlayerInstance && Dialogues.Num() > 0)
	{
		FTimerHandle TimerHandle;
		
		DialogueIndex++;

		PlayerInstance->DisableMovement();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("DialogueIndex: %d, DialogueIndex: %d"), DialoguesIndex, DialogueIndex));

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
		// After first conversation
		else if (DialoguesIndex == 0 && DialogueIndex == Dialogues[DialoguesIndex].DialogueList.Num())
		{
			DialogueWidgetInstance->RemoveFromViewport();
			DialogueIndex = 0;
			DialoguesIndex++;

			PlayerInstance->StartFadeOut(3.f);

			// Spawn the sword on the table and change a swordless mesh for the player
			if (SwordOnTable && SwordlessMaterial)
			{
				// Creating the sword instance to the game world
				SwordInstance = GetWorld()->SpawnActor<APlayerSword>(SwordLocation, SwordRotation);
				SwordInstance->SwordMesh->SetStaticMesh(SwordOnTable);

				// Making the sword disappear from the knight's back
				USkeletalMeshComponent* PlayerMesh = PlayerInstance->GetMesh();
				PlayerMesh->SetMaterial(3, SwordlessMaterial);
			}

			PlayerInstance->StartFadeIn(3.f);
			GetWorldTimerManager().SetTimer(TimerHandle, DelayDelegate, 0.5f, false);

		}
		// After second conversation
		else if (DialoguesIndex == 1 && DialogueIndex == Dialogues[DialoguesIndex].DialogueList.Num())
		{
			DialogueWidgetInstance->RemoveFromViewport();
			DialogueIndex = 0;
			DialoguesIndex++;

			PlayerInstance->StartFadeOut(3.f);

			// Destroy the sword on the table and change a mesh with sword for the player
			if (SwordInstance && NormalMaterial && HankeyToSpawn)
			{
				// Switch sword from the table on the back
				SwordInstance->Destroy();
				USkeletalMeshComponent* PlayerMesh = PlayerInstance->GetMesh();
				PlayerMesh->SetMaterial(3, NormalMaterial);

				// Creating the bloody cloth instance to the game world
				BloodyClothInstance = GetWorld()->SpawnActor<AKeyItem>(HankeyToSpawn, ClothLocation, ClothRotation);
				BloodyClothInstance->BoxComp->SetCollisionProfileName(TEXT("NoCollision"));
			}

			PlayerInstance->StartFadeIn(3.f);
			GetWorldTimerManager().SetTimer(TimerHandle, DelayDelegate, 0.5f, false);
		}
		// After the third conversation
		else if (DialoguesIndex == 2 && DialogueIndex == Dialogues[DialoguesIndex].DialogueList.Num())
		{
			DialogueWidgetInstance->RemoveFromViewport();
			DialogueIndex = -1;
			DialoguesIndex++;

			// Setting up the bloody cloth for interaction
			BloodyClothInstance->bInteractionEnabled = true;
			BloodyClothInstance->BoxComp->SetCollisionProfileName(TEXT("Interactable"));
			PlayerInstance->EnableMovement();
		}
		else
		{
			DialogueWidgetInstance->RemoveFromViewport();
			DialogueIndex = -1;
			PlayerInstance->EnableMovement();
		}
	}
}
