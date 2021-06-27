// Fill out your copyright notice in the Description page of Project Settings.


#include "FLCharacterAnimInstance.h"
#include "../../Components/PlayerCharacterMovementComponent.h"
#include "../MyFLCharacter.h"

void UFLCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	/** Make sure the TryGetPawnOwner()'s object belongs to the AMyFLCharacter for the STATIC_CAST implementation, through the checkf macros */
	checkf(TryGetPawnOwner()->IsA<AMyFLCharacter>(), TEXT("UFLCharacterAnimInstance can be used only with the MyFLCharacter class"));
	CachedCharacter = StaticCast<AMyFLCharacter*>(TryGetPawnOwner());
}

void UFLCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	/** If the CachedBaseCharacter isn't found implement early return */
	if (!CachedCharacter.IsValid())
	{
		return;
	}

	UPlayerCharacterMovementComponent* MovementComponent = CachedCharacter->GetPlayerCharacterMovement();
	Speed = MovementComponent->Velocity.Size();
	bIsInAir = MovementComponent->IsFalling();
	bIsCrouching = CachedCharacter->GetIsCrouching();
	bIsSprinting = MovementComponent->GetIsSprinting();
	bIsSwimming = MovementComponent->IsSwimming();
	
}
