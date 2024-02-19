// Fill out your copyright notice in the Description page of Project Settings.


#include "Altar.h"
#include "Components/BoxComponent.h"
#include "../../UI/OptionWidget.h"
#include "Kismet/GameplayStatics.h"

AAltar::AAltar()
{
	OptionWidgetInstance = nullptr;
	PlayerInstance = nullptr;
}

void AAltar::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (OptionWidget)
	{
		if (!OptionWidgetInstance)
		{
			OptionWidgetInstance = CreateWidget<UUserWidget>(PlayerController, OptionWidget);
		}
	}

	GetPlayerCharacter();
}

void AAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAltar::InteractWithMe()
{
	Super::InteractWithMe();
	ShowOptions();
}

void AAltar::ShowInteractionWidget()
{
	Super::ShowInteractionWidget();
}

void AAltar::HideInteractionWidget()
{
	Super::HideInteractionWidget();
}

void AAltar::PlayAnimation()
{

}

void AAltar::ShowOptions()
{
	if (OptionWidgetInstance && PlayerInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Altar interact"));
		PlayerInstance->DisableMovement();

		OptionWidgetInstance->AddToViewport();

		PlayerInstance->bIsPaused = true;
	}
}

// Gets reference to the player character
void AAltar::GetPlayerCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController)
	{
		// Get the character controlled by the player controller
		PlayerInstance = Cast<APlayerCharacter>(PlayerController->GetPawn());
	}
}
