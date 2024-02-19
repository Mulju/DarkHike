// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../KeyItem.h"
#include "Knife.generated.h"

/**
 * 
 */
UCLASS()
class DARKHIKE_API AKnife : public AKeyItem
{
	GENERATED_BODY()
	
public:

	virtual void InteractWithMe() override;
};
