// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API AFLPlayerController : public APlayerController
{
	GENERATED_BODY()

	/** SetPawn method of controller allows us to initialize the CachedCharacter through whom we will call his methods*/
	virtual void SetPawn(APawn* InPawn) override;

protected:

	/** Method responsible to Bind the nrcessary inputs */
	virtual void SetupInputComponent() override;

	/**
	* Create a pointer to our Character's to call the necessary functions from it
	* Must be SoftObjectPtr, to escape the memory leak when the pawn is destroied
	* Is initialized in the SetPawn(APawn InPawn) virtual method
	*/
	TSoftObjectPtr<class AFLBaseCharacter> CachedCharacter;

	/** The list of methods pending to be bound through the SetupInputComponent() virtual method */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);


	void Mantle();
	void Jump();
	void Crouch();

	void StartSprint();
	void StopSprint();

	void SwimForward(float Value);
	void SwimRight(float Value);
	void SwimUp(float Value);
};
