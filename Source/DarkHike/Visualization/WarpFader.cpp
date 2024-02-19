// Fill out your copyright notice in the Description page of Project Settings.


#include "WarpFader.h"
#include "Player/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWarpFader::AWarpFader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiating your class Components
	InteractComp = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractComp"));
	RootComponent = InteractComp;

	// Setting initial box extents
	InteractComp->SetBoxExtent(FVector(30.f, 50.f, 100.f), true);
	InteractComp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	InteractComp->OnComponentBeginOverlap.AddDynamic(this, &AWarpFader::OnInteractCompBeginOverlap);
	
}

// Called when the game starts or when spawned
void AWarpFader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarpFader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWarpFader::ResetCollisionPreset()
{
	InteractComp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void AWarpFader::OnInteractCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

			if (bIsTeleportTargetOffGround)
			{
				// Disable player movement
				PlayerCharacter->DisableMovement();
			}

			// Move the player character to the WarpLocation
			PlayerCharacter->SetActorLocation(WarpLocation);

			if (bIsTeleportTargetOffGround)
			{
				// Enable player movement
				PlayerCharacter->EnableMovement();
			}

			/*
			// Check if falling after the teleport
			if (PlayerCharacter->GetCharacterMovement()->IsFalling())
			{
				//PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
			}
			*/

			// Start the fade-in effect
			PlayerCharacter->StartFadeIn(FadeInTime);
		}
	}
}



