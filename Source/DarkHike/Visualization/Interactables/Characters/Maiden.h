// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableCharacter.h"
#include "Maiden.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API AMaiden : public AInteractableCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMaiden();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void InteractWithMe() override;

	bool bHasFirstInteraction = false;

};
