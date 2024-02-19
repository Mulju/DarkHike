// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableObject.h"
#include "../../Player/PlayerCharacter.h"
#include "InteractableRope.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRopeInteractionEvent);

/**
 * 
 */
UCLASS()
class DARKHIKE_API AInteractableRope : public AInteractableObject
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

	virtual void InteractWithMe() override;
	
	void ShowOptions();
	void GetPlayerCharacter();

	UPROPERTY(BlueprintAssignable)
	FRopeInteractionEvent OnRopeInteractionEvent;

	UPROPERTY(EditAnywhere, Category = "Priest Mesh")
	USkeletalMesh* CrushedPriestMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> KilledPriest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector KillLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator KillRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayTime = 1.f;

	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> RopeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* RopeWidgetInstance;

	UFUNCTION(BlueprintCallable)
	void CloseRopeWidget();
	
private:

	FTimerDelegate DelayDelegate;

	APlayerCharacter* PlayerInstance;
};
