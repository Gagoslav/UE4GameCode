// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FLBaseCharacter.generated.h"
/**
* Common Abstract class for all the Characters
* containing the pure virtual methods needed to be
* overriden in the inherited classes
*/

class UPlayerCharacterMovementComponent;
UCLASS(Abstract, NotBlueprintable)
class MYFIRSTHOMEWORK_API AFLBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	/** In constructor we call the FObjectInitializer structure to introduce new properly created movement component*/
	AFLBaseCharacter(const FObjectInitializer& ObjectInitializer);

	/** Getter for our properly created PlayerCharacterMovement component */
	FORCEINLINE UPlayerCharacterMovementComponent* GetPlayerCharacterMovement() { return MyMovementComponent; }

	/** The list of main function the Character will perform in the game */
	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void LookUp(float Value) {};
	virtual void Turn(float Value) {};
	virtual void ChangeCrouchState() {};
	virtual void StartSprint() {};
	virtual void StopSprint() {};
	virtual void SwimForward(float Value) {};
	virtual void SwimRight(float Value) {};
	virtual void SwimUp(float Value) {};
	virtual void Mantle();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Movement")
	class ULedgeDetectorComponent* LedgeDetectorComponent;

private:

	UPlayerCharacterMovementComponent* MyMovementComponent;

};
