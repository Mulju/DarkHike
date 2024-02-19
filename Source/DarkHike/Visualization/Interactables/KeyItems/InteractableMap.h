// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableObject.h"
#include "../../Player/PlayerCharacter.h"
#include "InteractableMap.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API AInteractableMap : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void InteractWithMe() override;

	void PlayAnimation();
	void ShowOptions();

	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MapWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* MapWidgetInstance;

	UPROPERTY()
	class AActor* Stairs;

	UPROPERTY(EditAnywhere, Category = "Choice Options")
	TArray<FString> OptionArray;

	APlayerCharacter* PlayerInstance;

	void GetPlayerCharacter();

	void AddToIntentory();

	UFUNCTION(BlueprintCallable)
	void CloseMapWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troll Variables")
	FVector TrollDeathLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troll Variables")
	FVector TrollRavenLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troll Variables")
	FVector TrollEatLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troll Variables")
	FRotator TrollDeathRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troll Variables")
	FRotator TrollRavenRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troll Variables")
	FRotator TrollEatRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair Variables")
	FVector StairLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair Variables")
	FRotator StairRotation;
};
