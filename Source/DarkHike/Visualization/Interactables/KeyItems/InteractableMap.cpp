// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableMap.h"
#include <Kismet/GameplayStatics.h>


AInteractableMap::AInteractableMap()
{
    TrollDeathLocation = FVector(4849.f, 7335.f, 1000.f);
    TrollDeathRotation = FRotator(11.f, -178.f, -83.f);
    
    TrollRavenLocation = FVector(5399.f, 8145.f, 1000.f);
    TrollRavenRotation = FRotator(0.f, -8.7f, 0.f);

    TrollEatLocation = FVector(5949.f, 6565.f, 1000.f);
    TrollEatRotation = FRotator(0.f, -118.f, 0.f);

    StairLocation = FVector(4830.f, 6060.f, 1366.f);
    StairRotation = FRotator(0.f, 0.f, 0.f);
    
    PlayerInstance = nullptr;
    //OptionWidgetInstance = nullptr;
    MapWidgetInstance = nullptr;
    PlayerController = nullptr;
}

void AInteractableMap::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (MapWidget)
    {
        if (!MapWidgetInstance)
        {
            MapWidgetInstance = CreateWidget<UUserWidget>(PlayerController, MapWidget);
        }
    }

    GetPlayerCharacter();
}

void AInteractableMap::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractableMap::InteractWithMe()
{
    Super::InteractWithMe();
    ShowOptions();
}

void AInteractableMap::PlayAnimation()
{
}

void AInteractableMap::ShowOptions()
{
    if (MapWidgetInstance && PlayerInstance && OptionArray.Num() == 3)
    {
        PlayerInstance->DisableMovement();

        MapWidgetInstance->AddToViewport();

        PlayerInstance->bIsPaused = true;
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Got here"));
    }
}

void AInteractableMap::GetPlayerCharacter()
{
    if (PlayerController)
    {
        // Get the character controlled by the player controller
        PlayerInstance = Cast<APlayerCharacter>(PlayerController->GetPawn());
    }
}

void AInteractableMap::AddToIntentory()
{

}

void AInteractableMap::CloseMapWidget()
{
    if (MapWidgetInstance && MapWidgetInstance->IsVisible())
    {
        MapWidgetInstance->RemoveFromViewport();
    }
}