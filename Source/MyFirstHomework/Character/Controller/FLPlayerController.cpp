// Fill out your copyright notice in the Description page of Project Settings.


#include "FLPlayerController.h"
#include "../FLBaseCharacter.h"

void AFLPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedCharacter = Cast<AFLBaseCharacter>(InPawn);
}

void AFLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AFLPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFLPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AFLPlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AFLPlayerController::Turn);
	InputComponent->BindAction("Mantle", IE_Pressed, this, &AFLPlayerController::Mantle);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFLPlayerController::Jump);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AFLPlayerController::Crouch);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFLPlayerController::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFLPlayerController::StopSprint);
	InputComponent->BindAxis("SwimForward", this, &AFLPlayerController::SwimForward);
	InputComponent->BindAxis("SwimRight", this, &AFLPlayerController::SwimRight);
	InputComponent->BindAxis("SwimUp", this, &AFLPlayerController::SwimUp);

}

void AFLPlayerController::MoveForward(float Value)
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->MoveForward(Value);
	}
}

void AFLPlayerController::MoveRight(float Value)
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->MoveRight(Value);
	}
}

void AFLPlayerController::LookUp(float Value)
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->LookUp(Value);
	}
}

void AFLPlayerController::Turn(float Value)
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->Turn(Value);
	}
}

void AFLPlayerController::Mantle()
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->Mantle();
	}
}

void AFLPlayerController::Jump()
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->Jump();
	}
}

void AFLPlayerController::Crouch()
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->ChangeCrouchState();
	}
}

void AFLPlayerController::StartSprint()
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->StartSprint();
	}
}

void AFLPlayerController::StopSprint()
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->StopSprint();
	}
}

void AFLPlayerController::SwimForward(float Value)
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->SwimForward(Value);
	}
}

void AFLPlayerController::SwimRight(float Value)
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->SwimRight(Value);
	}
}

void AFLPlayerController::SwimUp(float Value)
{
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->SwimUp(Value);
	}
}
