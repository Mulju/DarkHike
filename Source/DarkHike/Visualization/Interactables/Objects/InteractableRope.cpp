// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableRope.h"
#include "Kismet/GameplayStatics.h"
#include "../Characters/Priest.h"

void AInteractableRope::BeginPlay()
{
	Super::BeginPlay();

	DelayDelegate.BindLambda([&]()
		{
			PlayerInstance->EnableMovement();
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here"));
		});

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (RopeWidget)
	{
		if (!RopeWidgetInstance)
		{
			RopeWidgetInstance = CreateWidget<UUserWidget>(PlayerController, RopeWidget);
		}
	}

	GetPlayerCharacter();
}

void AInteractableRope::InteractWithMe()
{
	Super::InteractWithMe();

	ShowOptions();

	// This functionality is moved to the RopeWidget

	/*TArray<AActor*> FoundPriests;
	FName Priest = TEXT("Priest");
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), APriest::StaticClass(), Priest, FoundPriests);

	TArray<AActor*> FoundDestroyables;
	FName Destroyable = TEXT("Destroyable");
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Destroyable, FoundDestroyables);

	//FString DebugMessage = FString::Printf(TEXT("Found %d actors."), FoundActors.Num());
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);

	if (FoundPriests.Num() == 1 && FoundDestroyables.Num() == 2)
	{
		// Change the priest blueprint to crushed chandelier blueprint
		APriest* PriestInstance = Cast<APriest>(FoundPriests[0]);
		
		if (PriestInstance && KilledPriest)
		{
			// Destroy the priest instance
			PriestInstance->Destroy();
			
			// Creating the crushed priest into the game world
			GetWorld()->SpawnActor<AActor>(KilledPriest, KillLocation, KillRotation);
			
		}

		FoundDestroyables[0]->Destroy();
		FoundDestroyables[1]->Destroy();

		bInteractionEnabled = false;
		OnRopeInteractionEvent.Broadcast();

		// Disable movement for a while
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (PlayerController)
		{
			// Get the character controlled by the player controller
			PlayerInstance = Cast<APlayerCharacter>(PlayerController->GetPawn());

			if (PlayerInstance)
			{
				PlayerInstance->DisableMovement();
				FTimerHandle DelayTimerHandle;
				GetWorldTimerManager().SetTimer(DelayTimerHandle, DelayDelegate, DelayTime, false);
			}
		}
	}*/
}

void AInteractableRope::ShowOptions()
{
	if (RopeWidgetInstance && PlayerInstance)
	{
		PlayerInstance->DisableMovement();

		RopeWidgetInstance->AddToViewport();
	}
}

void AInteractableRope::GetPlayerCharacter()
{
	if (PlayerController)
	{
		// Get the character controlled by the player controller
		PlayerInstance = Cast<APlayerCharacter>(PlayerController->GetPawn());
	}
}

void AInteractableRope::CloseRopeWidget()
{
	if (RopeWidgetInstance && RopeWidgetInstance->IsVisible())
	{
		RopeWidgetInstance->RemoveFromViewport();
	}
}
