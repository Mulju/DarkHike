// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceDarkHike.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API UGameInstanceDarkHike : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int goodBadScore = 0;
};
