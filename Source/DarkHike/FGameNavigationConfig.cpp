// Fill out your copyright notice in the Description page of Project Settings.


#include "FGameNavigationConfig.h"

FGameNavigationConfig::FGameNavigationConfig()
{
	// Keyboard UI navigation
	KeyEventRules.Emplace(EKeys::A, EUINavigation::Left);
	KeyEventRules.Emplace(EKeys::D, EUINavigation::Right);
	KeyEventRules.Emplace(EKeys::W, EUINavigation::Up);
	KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);

	// Gamepad UI navigation
	//KeyEventRules.Emplace(EKeys::, EUINavigation::Up);
	//KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);
}

FGameNavigationConfig::~FGameNavigationConfig()
{

}
