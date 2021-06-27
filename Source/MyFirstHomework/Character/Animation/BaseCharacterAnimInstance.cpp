// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterAnimInstance.h"
#include "../MyThirdPersonCharacter.h"
#include "../../Components/MyTPCPawnMovementComponent.h"

void UBaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	/** Make sure the TryGetPawnOwner()'s object belongs to the AMyThirdPersonCharacter for the STATIC_CAST implementation, through the checkf macros */
	checkf(TryGetPawnOwner()->IsA<AMyThirdPersonCharacter>(), TEXT("UBaseCharacterAnimInstance::NativeBeginPlay only UBaseCharacterAnimInstance can work with BaseCharacterAnimInstance"));
	CachedBaseCharacter = StaticCast<AMyThirdPersonCharacter*>(TryGetPawnOwner());
}

void UBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	/** If the CachedBaseCharacter isn't found implement early return */
	if (!CachedBaseCharacter.IsValid())
	{
		return;
	}

	ForwardVector = CachedBaseCharacter->GetForwardVector();
	RightVector = CachedBaseCharacter->GetRightVector();
	bIsInAir = CachedBaseCharacter->GetMovementComponent()->IsFalling();

}
