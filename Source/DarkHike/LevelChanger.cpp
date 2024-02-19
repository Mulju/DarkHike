// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChanger.h"
#include "Visualization/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelChanger::ALevelChanger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiating your class Components
	InteractComp = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractComp"));
	RootComponent = InteractComp;

	// Setting initial box extents
	InteractComp->SetBoxExtent(FVector(30.f, 50.f, 100.f), true);
	InteractComp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	InteractComp->OnComponentBeginOverlap.AddDynamic(this, &ALevelChanger::OnInteractCompBeginOverlap);

}

// Called when the game starts or when spawned
void ALevelChanger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChanger::OnInteractCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is the player character
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

		if (PlayerCharacter)
		{
			// The player character has overlapped with the InteractComp

			// Start the fade-out effect
			PlayerCharacter->StartFadeOut(FadeOutTime);

			// Delay for 0.5 seconds before moving the player character
			FTimerHandle DelayTimerHandle;

			// Call the delay function
			GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [this]() { return; }, FadeOutTime, false);

			// Change level after delay
			if (LevelToLoad.IsValidXName())
			{
				UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("The level to load hasn't been set."));
			}
		}
	}
}