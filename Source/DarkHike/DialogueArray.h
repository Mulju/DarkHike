// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueArray.generated.h"

USTRUCT(BlueprintType)
struct DARKHIKE_API FDialogueArray
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FString> DialogueList;
	FDialogueArray();
	~FDialogueArray();
};
