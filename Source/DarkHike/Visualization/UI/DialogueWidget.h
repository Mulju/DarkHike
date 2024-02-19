// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetDialogueText(FString DialogueString);

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogueText;
};
