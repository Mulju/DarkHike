// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableCharacter.h"
#include "GenericSoul.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API AGenericSoul : public AInteractableCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void InteractWithMe() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInteractedWith = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LerpVariable = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator OriginalRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRotatingCharacter = true;
};
