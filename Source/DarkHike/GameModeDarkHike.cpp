// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeDarkHike.h"
#include "Framework/Application/SlateApplication.h"

AGameModeDarkHike::AGameModeDarkHike() : gameNavigationConfig(MakeShared<FGameNavigationConfig>())
{ }

void AGameModeDarkHike::BeginPlay()
{
	Super::BeginPlay();

	FSlateApplication::Get().SetNavigationConfig(gameNavigationConfig);
}
