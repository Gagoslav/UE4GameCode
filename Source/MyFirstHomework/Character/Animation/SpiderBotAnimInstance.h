// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterAnimInstance.h"
#include "SpiderBotAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API USpiderBotAnimInstance : public UBaseCharacterAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	/** Vectors variables containing several effectors' locations */
	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category = "Spider Bot | IK Settings")
	FVector RightFrontFootEffectorLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category = "Spider Bot | IK Settings")
	FVector RightRearFootEffectorLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category = "Spider Bot | IK Settings")
	FVector LeftFrontFootEffectorLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category = "Spider Bot | IK Settings")
	FVector LeftRearFootEffectorLocation = FVector::ZeroVector;


	/**
	* Create a pointer to our ASpiderBotPawn's to get the necessary values from it
	* Must be WeakObjectPtr, to escape the memory leak when the pawn is destroied
	*/
	TWeakObjectPtr<class ASpiderBotPawn> CachedCharacter;

};
