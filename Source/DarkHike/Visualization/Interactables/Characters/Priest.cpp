// Fill out your copyright notice in the Description page of Project Settings.


#include "Priest.h"
#include "Kismet/GameplayStatics.h"
#include "../../UI/DialogueWidget.h"
#include "../InteractableObject.h"

void APriest::BeginPlay()
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
			bInteractionEnabled = true;
		});
}

void APriest::InteractWithMe()
{
	ShowDialogue();

	// Activating the rope on the first interaction
	if (!bHasFirstInteraction)
	{
		TArray<AActor*> FoundCovers;
		TArray<AActor*> FoundRopes;
		FName GraveCover = TEXT("GraveCover");
		FName Rope = TEXT("Rope");
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), GraveCover, FoundCovers);
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), Rope, FoundRopes);

		//FString DebugMessage = FString::Printf(TEXT("Found %d Ropes."), FoundRopes.Num());
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);

		//FString DebugMessage2 = FString::Printf(TEXT("Found %d Grave covers."), FoundCovers.Num());
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage2);

		if (FoundCovers.Num() == 1 && FoundRopes.Num() == 1)
		{
			// Move the grave cover
			FoundCovers[0]->SetActorLocationAndRotation(GraveSlabLocation, GraveSlabLRotation);

			// Enable interaction with the rope
			AInteractableObject* RopeInstance = Cast<AInteractableObject>(FoundRopes[0]);
			if (RopeInstance)
			{
				RopeInstance->bInteractionEnabled = true;
			}
		}

		OnCharacterInteractionEvent.Broadcast();
		bHasFirstInteraction = true;
	}
}

void APriest::ShowDialogue()
{
	if (DialogueWidgetInstance && PlayerInstance && Dialogues.Num() > 0)
	{
		FTimerHandle TimerHandle;
		
		DialogueIndex++;

		PlayerInstance->DisableMovement();

		if (DialoguesIndex == 0 && DialogueIndex == 6)
		{
			bInteractionEnabled = false;
			DialogueWidgetInstance->RemoveFromViewport();
			bIsHearingSound = true;
			GetWorldTimerManager().SetTimer(TimerHandle, DelayDelegate, 1.5f, false);

			// Get reference to the guy from the catacombs
			TArray<AActor*> FoundGuys;
			FName Grave = TEXT("Grave");
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), Grave, FoundGuys);

			if (FoundGuys.Num() == 1)
			{
				// Destroy the grave cover
				FoundGuys[0]->SetActorLocationAndRotation(GraveGuyLocation, GraveGuyLRotation);
			}
		}
		else if (DialogueIndex >= 0 && DialogueIndex < Dialogues[DialoguesIndex].DialogueList.Num())
		{
			DialogueWidgetInstance->AddToViewport();

			FString DialogueText = Dialogues[DialoguesIndex].DialogueList[DialogueIndex];

			if (DialogueWidgetInstance)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here"));
				DialogueWidgetInstance->SetDialogueText(DialogueText);
			}
		}
		// After first conversation set the dialogue for 2
		else if (DialoguesIndex == 0 && DialogueIndex == Dialogues[DialoguesIndex].DialogueList.Num())
		{
			DialogueWidgetInstance->RemoveFromViewport();
			DialogueIndex = -1;
			DialoguesIndex = 2;
			PlayerInstance->EnableMovement();
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

void APriest::SetDialoguesIndex(int index)
{
	if (index >= 0 && index < Dialogues.Num())
	{
		DialoguesIndex = index;
	}
}
