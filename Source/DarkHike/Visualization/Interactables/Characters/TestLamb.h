// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableCharacter.h"
#include "TestLamb.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API ATestLamb : public AInteractableCharacter
{
	GENERATED_BODY()

public:

	virtual void InteractWithMe() override;
	
};
