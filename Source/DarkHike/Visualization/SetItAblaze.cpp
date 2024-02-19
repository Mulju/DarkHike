// Fill out your copyright notice in the Description page of Project Settings.

#include "SetItAblaze.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASetItAblaze::ASetItAblaze()
{
    /*
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
    OurParticleSystem->SetupAttachment(RootComponent);
    OurParticleSystem->bAutoActivate = false;
    //OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
    if (ParticleAsset.Succeeded())
    {
        OurParticleSystem->SetTemplate(ParticleAsset.Object);
    }
    */
}

// Called when the game starts or when spawned
void ASetItAblaze::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetItAblaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*

*/

void ASetItAblaze::ParticleToggle()
{
    /*
    if (OurParticleSystem && OurParticleSystem->Template)
    {
        OurParticleSystem->ToggleActive();
    }
    */
}