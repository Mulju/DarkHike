// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "../Player/PlayerCharacter.h"
#include "../../DialogueArray.h"
#include "InteractableLoreItem.generated.h"

UCLASS()
class DARKHIKE_API AInteractableLoreItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableLoreItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInteractionEnabled = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY()
	class UDialogueWidget* DialogueWidgetInstance;

	UPROPERTY(EditAnywhere, Category = "Dialogue System")
	TArray<FDialogueArray> Dialogues;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue System")
	int DialoguesIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue System")
	int DialogueIndex;

	APlayerCharacter* PlayerInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool CheckInteraction() override;
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	void ShowDialogue();

	UFUNCTION(BlueprintCallable)
	void RotateWidgetToCamera();

private:
	UPROPERTY(EditAnywhere)
	class USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ObjectMesh;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* InteractionWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDialogueWidget> DialogueWidget;

	void GetPlayerCharacter();
};
