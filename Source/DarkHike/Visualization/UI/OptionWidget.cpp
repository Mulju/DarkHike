// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidget.h"
#include "Components/TextBlock.h"

void UOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UOptionWidget::SetOptionText(TArray<FString> OptionArray)
{
	if (OptionTextOne)
	{
		OptionTextOne->SetText(FText::FromString(OptionArray[0]));
	}

	if (OptionTextTwo)
	{
		OptionTextTwo->SetText(FText::FromString(OptionArray[1]));
	}

	if (OptionTextThree)
	{
		OptionTextThree->SetText(FText::FromString(OptionArray[2]));
	}
}
