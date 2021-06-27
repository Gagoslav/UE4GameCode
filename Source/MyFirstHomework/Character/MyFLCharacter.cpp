// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFLCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "../Components/PlayerCharacterMovementComponent.h"
#include "Components/TimelineComponent.h"


AMyFLCharacter::AMyFLCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = 1;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	/** Make the Character to change it's orientation by movement in Yaw axis and Yaw, Pitch in water */
	GetPlayerCharacterMovement()->bOrientRotationToMovement = 1;
	GetPlayerCharacterMovement()->RotationRate.Yaw = 540.0f;
	GetPlayerCharacterMovement()->RotationRate.Pitch = 540.0f;
	
}


void AMyFLCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(SprintCurve))
	{
		FOnTimelineFloat SprintTimelineFunction;
		SprintTimelineFunction.BindUFunction(this, FName("UpdateSprintTimeline"));
		SprintTimeline.AddInterpFloat(SprintCurve, SprintTimelineFunction);
	}
}

void AMyFLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SprintTimeline.TickTimeline(DeltaTime);
}

void AMyFLCharacter::MoveForward(float Value)
{
	if (GetPlayerCharacterMovement()->IsMovingOnGround() || GetPlayerCharacterMovement()->IsFalling())
	{
		if (!FMath::IsNearlyZero(Value, 1e-6f))
		{
			FRotator YawRotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
			FVector Forward = YawRotator.RotateVector(FVector::ForwardVector);
			AddMovementInput(Forward, Value);
		}
	}
}

void AMyFLCharacter::MoveRight(float Value)
{
	if (GetPlayerCharacterMovement()->IsMovingOnGround() || GetPlayerCharacterMovement()->IsFalling())
	{
		if (!FMath::IsNearlyZero(Value, 1e-6f))
		{
			FRotator YawRotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
			FVector Right = YawRotator.RotateVector(FVector::RightVector);
			AddMovementInput(Right, Value);
		}
	}
	
}

void AMyFLCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyFLCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMyFLCharacter::ChangeCrouchState()
{
	if (!bIsCrouched && CanCrouch())
	{
		Crouch();
		bIsCrouched = true;
		
	}
	else
	{
		UnCrouch();
		bIsCrouched = false;
	}
}

void AMyFLCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	/** Prevent camera's cutting movement when crouched*/
	SpringArm->TargetOffset.Z += HalfHeightAdjust;
}

void AMyFLCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	/** Prevent camera's cutting movement when uncrouched*/
	SpringArm->TargetOffset.Z -= HalfHeightAdjust;
}

bool AMyFLCharacter::CanJumpInternal_Implementation() const
{
	/** Character can always jump, despite crouching */
	return bIsCrouched || Super::CanJumpInternal_Implementation();
}

void AMyFLCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	if (bIsCrouched)
	{
		ChangeCrouchState();
	}
	
	
}

void AMyFLCharacter::StartSprint()
{
	if (GetPlayerCharacterMovement()->IsMovingOnGround())
	{
		if (bIsCrouched)
		{
			ChangeCrouchState();
		}
		DefaultWalkSpeed = GetPlayerCharacterMovement()->MaxWalkSpeed;
		/** Increase character's speed */
		GetPlayerCharacterMovement()->MaxWalkSpeed = GetPlayerCharacterMovement()->MaxSprintSpeed;
		GetPlayerCharacterMovement()->bForceMaxAccel = 1;
		OnStartSprint();
	}
}

void AMyFLCharacter::StopSprint()
{
	/** Returns character's speed to the default value */
	GetPlayerCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	GetPlayerCharacterMovement()->bForceMaxAccel = 0;
	OnEndSprint();
}

void AMyFLCharacter::OnStartSprint_Implementation()
{
	SprintTimeline.Play();
}

void AMyFLCharacter::OnEndSprint_Implementation()
{
	SprintTimeline.Reverse();
}

void AMyFLCharacter::SwimForward(float Value)
{
	if (GetPlayerCharacterMovement()->IsSwimming() && !FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator PitchYawRotate = FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw, 0.0);
		FVector Forward = PitchYawRotate.RotateVector(FVector::ForwardVector);
		AddMovementInput(Forward, Value);

	}
}

void AMyFLCharacter::SwimRight(float Value)
{
	if (GetPlayerCharacterMovement()->IsSwimming() && !FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotate = FRotator(0.0, GetControlRotation().Yaw, 0.0);
		FVector Right = YawRotate.RotateVector(FVector::RightVector);
		AddMovementInput(Right, Value);
	}
}

void AMyFLCharacter::SwimUp(float Value)
{
	if (GetPlayerCharacterMovement()->IsSwimming()  && !FMath::IsNearlyZero(Value, 1e-6f))
	{
		AddMovementInput(FVector::UpVector, Value);
	}
}


void AMyFLCharacter::UpdateSprintTimeline(float Value)
{
	SpringArm->TargetArmLength = Value;
}



