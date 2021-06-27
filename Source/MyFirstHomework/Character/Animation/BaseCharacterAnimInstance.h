// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	/** Initialize (cast to  the needed class) our CachedBaseCharacter */
	virtual void NativeBeginPlay() override;

	/** Get the needed values each DeltaSecond to reinitialize the variables */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	/** Right and Forward fectors finder needed for the creation of a BlendSpace*/
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Config")
	float ForwardVector;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Config")
	float RightVector;

	/** Find a condition when the Jump animation will be played */
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Config")
	bool bIsInAir;

private:
	
	/** 
	* Create a pointer to our Pawn to get the necessary values from it
	* Must be WeakObjectPtr, to escape the memory leak when the pawn is destroied
	*/
	TWeakObjectPtr <class AMyThirdPersonCharacter> CachedBaseCharacter;
};
