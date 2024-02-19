// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSword.h"

// Sets default values
APlayerSword::APlayerSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Instantiating and setting your class Components
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SwordMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

