// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FLCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API UFLCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	

public:

	/** Initialize (cast to  the needed class) our CachedBaseCharacter */
	virtual void NativeBeginPlay() override;

	/** Get the needed values each DeltaSecond to reinitialize the variables */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player settings")
	float Speed = 0.0f;

	/** Find a condition when the Jump animation will be played */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player settings")
	bool bIsInAir = false;

	/** Find a condition when the Crouch animation will be played */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player settings")
	bool bIsCrouching = false;

	/** Find a condition when the Sprint animation will be played */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player settings")
	bool bIsSprinting = false;

	/** Find a condition when the Swim animation will be played */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player settings")
	bool bIsSwimming = false;

private:
	
	/**
	* Create a pointer to our Character's to get the necessary values from it
	* Must be WeakObjectPtr, to escape the memory leak when the pawn is destroied
	*/
	TWeakObjectPtr<class AMyFLCharacter> CachedCharacter;
};
