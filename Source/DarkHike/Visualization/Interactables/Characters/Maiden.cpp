// Fill out your copyright notice in the Description page of Project Settings.


#include "Maiden.h"
#include "Kismet/GameplayStatics.h"
#include <DarkHike/Visualization/Interactables/Objects/Altar.h>

AMaiden::AMaiden()
{

}

void AMaiden::BeginPlay()
{
	Super::BeginPlay();
}

void AMaiden::InteractWithMe()
{
	Super::InteractWithMe();

	// Activating the altar on first interaction
	if (!bHasFirstInteraction)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAltar::StaticClass(), FoundActors);

		//FString DebugMessage = FString::Printf(TEXT("Found %d actors."), FoundActors.Num());
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);

		if (FoundActors.Num() == 1)
		{
			AAltar* AltarInstance = Cast<AAltar>(FoundActors[0]);

			if (AltarInstance)
			{
				AltarInstance->bInteractionEnabled = true;
			}
		}

		bHasFirstInteraction = true;
	}
}


