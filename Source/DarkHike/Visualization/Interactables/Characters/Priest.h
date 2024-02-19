// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableCharacter.h"
#include "Priest.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API APriest : public AInteractableCharacter
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void InteractWithMe() override;
	void ShowDialogue();

	UFUNCTION(BlueprintCallable)
	void SetDialoguesIndex(int index);

	bool bHasFirstInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector GraveGuyLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator GraveGuyLRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHearingSound = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector GraveSlabLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator GraveSlabLRotation;

private:

	FTimerDelegate DelayDelegate;

};
