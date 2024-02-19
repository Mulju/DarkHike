// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lamb.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavMesh/NavMeshBoundsVolume.h"
//#include "TimerManager.h"

#include "LambStateEnum.h"

#include "LambController.generated.h"

UCLASS()
class DARKHIKE_API ALambController : public AAIController
{
	GENERATED_BODY()

public: 
	ALambController();

	UPROPERTY(VisibleAnywhere, Category= "CPPLambCtrl")
	FString CtrldLambName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "CPPLambCtrl")
	ALamb* CtrldLamb;
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category= "CPPLambCtrl|State")
	bool bQuestActive;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "CPPLambCtrl|State")
	bool bAlive;
	UPROPERTY(VisibleAnywhere, Category= "CPPLambCtrl|State")
	bool bMoving;
	UPROPERTY(VisibleAnywhere, Category= "CPPLambCtrl|State")
	bool bAnimating;
	UPROPERTY(VisibleAnywhere, Category= "CPPLambCtrl|State")
	bool CRFP;

	UPROPERTY(EditAnywhere, Category= "CPPLambCtrl|State")
	TEnumAsByte<State> LambState;

	UPROPERTY(VisibleAnywhere, Category= "CPPLambCtrl|Debug")
	UPathFollowingComponent* LambPathFollowingComponent;

	UPROPERTY(VisibleAnywhere, Category= "CPPLambCtrl|Debug")
	FString LambPathStatusEnum;

	//Public Inherited Functions
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void EvaluateState();
	UFUNCTION(CallInEditor, BlueprintCallable, Category= "CPPLambCtrl|Functions")
	void StateGraze();
	UFUNCTION(CallInEditor, BlueprintCallable, Category= "CPPLambCtrl|Functions")
	void StateFollow();
	UFUNCTION(CallInEditor, Category= "CPPLambCtrl|Functions")
	void StateMove();
	UFUNCTION(CallInEditor, BlueprintCallable, Category= "CPPLambCtrl|Functions")
	void StateWait();
	UFUNCTION(CallInEditor, BlueprintCallable, Category= "CPPLambCtrl|Functions")
	void MoveToWaitZone();
	UFUNCTION(CallInEditor, BlueprintCallable, Category= "CPPLambCtrl|Functions")
	void MoveToSacrificeZone();
	UFUNCTION(CallInEditor, BlueprintCallable, Category= "CPPLambCtrl|Functions")
	void KillLamb();

protected:
	//Protected Inherited Functions
	virtual void BeginPlay() override;
	
};
