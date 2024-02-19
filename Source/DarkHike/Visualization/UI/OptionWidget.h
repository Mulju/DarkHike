// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API UOptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetOptionText(TArray<FString> OptionArray);

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UButton* ButtonToFocus;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* OptionTextOne;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* OptionTextTwo;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* OptionTextThree;
};
