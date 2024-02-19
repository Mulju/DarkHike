// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableObject.h"
#include "../../Player/PlayerCharacter.h"
#include "Altar.generated.h"

/**
 * 
 */

UCLASS()
class DARKHIKE_API AAltar : public AInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAltar();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	void PlayAnimation();
	void ShowOptions();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> OptionWidget;

	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* OptionWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Choice Options")
	TArray<FString> OptionArray;

	APlayerCharacter* PlayerInstance;

	void GetPlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice Options")
	bool bIsMaidenActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice Options")
	bool bIsLambActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice Options")
	bool bIsHandkerchiefActivated = false;
};
