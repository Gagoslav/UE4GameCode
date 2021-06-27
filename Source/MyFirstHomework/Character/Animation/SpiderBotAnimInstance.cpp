// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderBotAnimInstance.h"
#include "../Pawn/SpiderBotPawn.h"

void USpiderBotAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	/** Make sure the TryGetPawnOwner()'s object belongs to the ASpiderBotPawn for the STATIC_CAST implementation, through the checkf macros */
	checkf(TryGetPawnOwner()->IsA<ASpiderBotPawn>(),TEXT("Pawn can be only of a ASpiderBotPawn class "));
	CachedCharacter = StaticCast<ASpiderBotPawn*>(TryGetPawnOwner());
}

void USpiderBotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	/** If the CachedBaseCharacter isn't found implement early return */
	if (!CachedCharacter.IsValid())
	{
		return;
	}
	else
	{
		/** Set correct locations for each effector every frame */
		RightFrontFootEffectorLocation = FVector(CachedCharacter->GetFrontRightLegOffset(), 0.0f, 0.0f);
		RightRearFootEffectorLocation = FVector(CachedCharacter->GetRareRightLegOffset(), 0.0f, 0.0f);
		LeftFrontFootEffectorLocation = FVector(CachedCharacter->GetFrontLeftLegOffset(), 0.0f, 0.0f);
		LeftRearFootEffectorLocation = FVector(CachedCharacter->GetRareLeftLegOffset(), 0.0f, 0.0f);

	}
}