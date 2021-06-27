// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API UPlayerCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	bool GetIsSprinting() { return MaxWalkSpeed == MaxSprintSpeed; }


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprint Speed")
	float MaxSprintSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: Swimming ")
	float SwimmingCapsuleRadius = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: Swimming ")
	float SwimmingCapsuleHalfHeight = 40.0f;

protected:

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	
};
