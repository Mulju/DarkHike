// Fill out your copyright notice in the Description page of Project Settings.


#include "LambController.h"

ALambController::ALambController()
{
	// Init Inherited Settings
	PrimaryActorTick.bCanEverTick = true;
	CtrldLambName = "Default Lamb";
	CtrldLamb = nullptr;
	bQuestActive = false;
	bAlive = true;
	bMoving = false;
	bAnimating = false;
	LambState = Grazing;
	LambPathFollowingComponent = AAIController::GetPathFollowingComponent();

}

void ALambController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Init
	if (Cast<ALamb>(InPawn)) 
	{
		CtrldLamb = Cast<ALamb>(InPawn);
	} 
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed Pawn is not a Lamb"));
	}

	CtrldLambName = CtrldLamb->LambName;
	MovementComponent = CtrldLamb->GetCharacterMovement();
}

void ALambController::BeginPlay()
{
	Super::BeginPlay();

	//Init 
	/*if (ArrLambMovementZone.Num() < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("No zones have been assigned"));
	} */
	CRFP = this->bSetControlRotationFromPawnOrientation;

}

void ALambController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	EvaluateState();

}

void ALambController::EvaluateState()
{
	LambPathStatusEnum = LambPathFollowingComponent->GetStatusDesc();
	if (LambPathFollowingComponent)
	{
		bMoving = 
			(LambPathFollowingComponent->GetStatus() == EPathFollowingStatus::Moving) 
			? true : false;
	}

	if (LambState == Moving)
	{
		MovementComponent->MaxWalkSpeed = CtrldLamb->TrotSpeed;
	}

	if (LambState == Following)
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(CtrldLamb->PlayerActor);
		float PlayerSpeed = PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed;
		
		if (CtrldLamb->DistancePlayer < 250.0)
		{
			MovementComponent->MaxWalkSpeed = PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed;
		}
		else if (CtrldLamb->DistancePlayer > 250.0 && CtrldLamb->DistancePlayer < 550.0)
		{
			MovementComponent->MaxWalkSpeed = 1.25*(PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed);
		}
		else
		{
			MovementComponent->MaxWalkSpeed = 2.0*(PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed);
		}
	}
	
	switch (LambState)
	{
		case Grazing:
			StateGraze();
			break;
		case Following:
			StateFollow();
			break;
		case Moving:
			StateMove();
			break;
    	case Waiting:
			StateWait();
			break;
		default:
			//fuck my life
			break;
	}
}

void ALambController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//IsFailure(), IsInterrupted(), IsSuccess()

	//bMoving = false;
}

void ALambController::StateGraze()
{
	LambState = Grazing;
	FVector RandomLocation;
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	
	MovementComponent->MaxWalkSpeed = CtrldLamb->WalkSpeed;
	
	if (!bMoving)
	{
		if (NavSys)
		{
			NavSys->K2_GetRandomReachablePointInRadius( 
				GetWorld(), 
				CtrldLamb->GetActorLocation(), 
				RandomLocation, 
				600.0f);

			AAIController::MoveToLocation(RandomLocation);
			bMoving = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Navigation System Found"));
		}
	}
}

void ALambController::StateFollow()
{
	//MovementComponent->MaxWalkSpeed = CtrldLamb->RunSpeed;
	LambState = Following;
	if (!bMoving)
	{
		AAIController::MoveToActor(CtrldLamb->PlayerActor);
		bMoving = true;
	}
	else 
	{
		AAIController::MoveToActor(CtrldLamb->PlayerActor);
	}
}

void ALambController::StateMove()
{
	if (LambPathFollowingComponent->GetStatus() == EPathFollowingStatus::Idle)
	{
		StateWait();
		bMoving = false;
	}
}

void ALambController::StateWait()
{
	LambState = Waiting;
	if (LambPathFollowingComponent->GetStatus() != EPathFollowingStatus::Idle || LambPathFollowingComponent->GetStatus() != EPathFollowingStatus::Paused)
	{
		StopMovement();
	}
	SetFocus(CtrldLamb->PlayerActor, EAIFocusPriority::Default);
	UpdateControlRotation(4.5f, true);
}

void ALambController::MoveToWaitZone()
{
	if (CtrldLamb->GetActorLocation() != CtrldLamb->WaitZone->GetActorLocation())
	{
		AAIController::MoveToActor(CtrldLamb->WaitZone, 1.0f, false, true);
		LambState = Moving;
		bMoving = true;
	}
	else
	{
		LambState = Waiting;
	}
}

void ALambController::MoveToSacrificeZone()
{
	
	if (CtrldLamb->GetActorLocation() != CtrldLamb->SacrificeZone->GetActorLocation())
	{
		AAIController::MoveToActor(CtrldLamb->SacrificeZone, 1.0f, false, true);
		LambState = Moving;
		bMoving = true;
	}
	else
	{
		LambState = Waiting;
	}
}

void ALambController::KillLamb()
{
	bAlive = false;
}


