// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableCharacter.h"
#include "../../Player/PlayerSword.h"
#include "../KeyItem.h"
#include "Swordsmith.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API ASwordsmith : public AInteractableCharacter
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	virtual void InteractWithMe() override;
	
	void ShowDialogue();

	UPROPERTY(EditAnywhere)
	UStaticMesh* SwordOnTable;

	UPROPERTY(EditAnywhere)
	FVector SwordLocation;

	UPROPERTY(EditAnywhere)
	FRotator SwordRotation;

	UPROPERTY(EditAnywhere, Category = "Player Material")
	UMaterialInterface* SwordlessMaterial;

	UMaterialInterface* NormalMaterial;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AKeyItem> HankeyToSpawn;

	UPROPERTY(EditAnywhere)
	FVector ClothLocation;

	UPROPERTY(EditAnywhere)
	FRotator ClothRotation;

private:

	FTimerDelegate DelayDelegate;

	APlayerSword* SwordInstance;

	AKeyItem* BloodyClothInstance;
};
