// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyTPCPawnMovementComponent.generated.h"


/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API UMyTPCPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisFunction)override;

public:

	void JumpStart();

	virtual bool IsFalling()const override;

protected:
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	bool bEnableGravity;

	UPROPERTY(EditAnywhere)
	float InitialJumpVelocity = 500.0f;

private:
	FVector VerticalVelocity = FVector::ZeroVector;
	bool bIsFalling = false;
	
};
