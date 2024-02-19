// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGameNavigationConfig.h"
#include "GameModeDarkHike.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API AGameModeDarkHike : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeDarkHike();
	
	virtual void BeginPlay() override;

	TSharedRef<FGameNavigationConfig> gameNavigationConfig;
	
};
