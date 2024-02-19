// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelChanger.generated.h"

UCLASS()
class DARKHIKE_API ALevelChanger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelChanger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Player interact trigger
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* InteractComp;

	UFUNCTION()
	void OnInteractCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fade")
	float FadeOutTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Management")
	FName LevelToLoad;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
