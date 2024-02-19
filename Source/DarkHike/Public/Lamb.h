// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Visualization/Interactables/InteractableInterface.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "../DialogueArray.h"
#include "../Visualization/UI/DialogueWidget.h"
#include "DarkHike/Visualization/Player/PlayerCharacter.h"

#include "Lamb.generated.h"

UCLASS()
class DARKHIKE_API ALamb : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Public Functions
	ALamb();

	//Public Inherited Functions
	virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool CheckInteraction() override;
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	void ShowDialogue();

	UFUNCTION(BlueprintCallable)
	void RotateWidgetToCamera();

	UFUNCTION(BlueprintCallable)
	void IncreaseDialoguesIndex();

	//Public Variables
	AActor* PlayerActor;

	UPROPERTY(EditAnywhere, Category = "CPPLamb|Values")
	uint32 WalkSpeed;
	UPROPERTY(EditAnywhere, Category = "CPPLamb|Values")
	uint32 TrotSpeed;
	UPROPERTY(EditAnywhere, Category = "CPPLamb|Values")
	uint32 RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPPLamb")
	FString LambName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CPPLamb")
	bool bClearReached;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CPPLamb")
	bool bToSacrifice;

	UPROPERTY(VisibleAnywhere, Category = "CPPLamb|Debug")
	float DistancePlayer;

	UPROPERTY(EditAnywhere, Category = "CPPLamb|Zones")
	TArray<ANavMeshBoundsVolume*> ArrLambMovementZone; //Fill in Scene with Volumes to define where can move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CPPLamb|Zones")
	AActor* ClearZone;
	UPROPERTY(EditAnywhere, Category = "CPPLamb|Zones")
	AActor* SacrificeZone;
	UPROPERTY(EditAnywhere, Category = "CPPLamb|Zones")
	AActor* WaitZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInteractionEnabled = true;

	UPROPERTY()
	class UDialogueWidget* DialogueWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Dialogue System")
	TArray<FDialogueArray> Dialogues;

	int DialoguesIndex;
	int DialogueIndex;

	APlayerCharacter* PlayerInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

protected:
	// Protected Functions
	virtual void BeginPlay() override;

	void CalculateColliderSize();

private:
	//UPROPERTY(VisibleAnywhere, Category = "CPPLamb", meta = (AllowPrivateAccess = "True"))

	USceneComponent* ColliderMatchPivot;
	UCapsuleComponent* DefaultCapsuleComponent;
	USkeletalMeshComponent* DefaultSkeletalMeshComponent;
	UArrowComponent* DefaultArrow;

	USkeletalMesh* LambSkelMesh;

private:

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* InteractionWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDialogueWidget> DialogueWidget;

	void GetPlayerCharacter();

};
