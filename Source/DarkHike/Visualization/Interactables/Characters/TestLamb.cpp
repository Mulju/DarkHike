// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLamb.h"
#include <Kismet/GameplayStatics.h>
#include "../Objects/Altar.h"

void ATestLamb::InteractWithMe()
{
	Super::InteractWithMe();

	// Activating the maiden option of the altar
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAltar::StaticClass(), FoundActors);

	//FString DebugMessage = FString::Printf(TEXT("Found %d actors."), FoundActors.Num());
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);

	if (FoundActors.Num() == 1)
	{
		AAltar* AltarInstance = Cast<AAltar>(FoundActors[0]);

		if (AltarInstance)
		{
			AltarInstance->bIsLambActivated = true;
		}
	}
}
