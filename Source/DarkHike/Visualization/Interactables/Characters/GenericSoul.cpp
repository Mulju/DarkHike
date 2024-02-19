// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericSoul.h"

void AGenericSoul::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();
}

void AGenericSoul::InteractWithMe()
{
	if (DialogueIndex == -1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here first"));
		bIsInteractedWith = true;
		LerpVariable = 0.f;
	}

	Super::InteractWithMe();

	if (DialogueIndex == -1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here last"));
		bIsInteractedWith = false;
		LerpVariable = 0.f;
	}
}
