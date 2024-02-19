// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDialogueWidget::SetDialogueText(FString DialogueString)
{
	if (DialogueText)
	{
		DialogueText->SetText(FText::FromString(DialogueString));
	}
}
