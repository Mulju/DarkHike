// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interactables/InteractableInterface.h"
#include "../UI/OptionWidget.h"
#include "Components/Button.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DARKHIKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Fixed player follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spring Arm Component to follow the player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	float SprintSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properties")
	float InteractionDistance = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Fade")
	float FadeInAtStartDuration = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Fade")
	bool FadeInAtStart = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Fade")
	float FadeOutDuration = 2.0f;

	// Called for forwards/backward input
	void MoveForward(float InputAxis);

	// Called for left/right side input
	void MoveRight(float InputAxis);

	// Sets Character Movement Speed to Sprint values.
	void BeginSprint();

	// Sets Character Movement Speed back to default speed values.
	void EndSprint();

	// Interact with interactable actors
	void OnInteract();

	// Checks overlapping actors for interactable actors
	void CheckOverlappingInteractables();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Starts the screen fade in
	UFUNCTION(BlueprintCallable, Category = "Scene Fade")
	void StartFadeIn(float FadeTime);
	
	// Starts the screen fade out
	UFUNCTION(BlueprintCallable, Category = "Scene Fade")
	void StartFadeOut(float FadeTime);

	// Enables player movement
	void EnableMovement();

	// Disables player movement
	void DisableMovement();

	// Change the focus on the widget options
	void SetFocusOnOptionWidget(UButton* WidgetToFocus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Paused")
	bool bIsPaused;

	UPROPERTY(BlueprintReadOnly)
	AActor* ClosestActor;

private:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* InteractionBox;

	IInteractableInterface* Interface = nullptr;
};
