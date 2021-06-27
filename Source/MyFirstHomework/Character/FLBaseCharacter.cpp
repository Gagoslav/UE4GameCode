// Fill out your copyright notice in the Description page of Project Settings.


#include "FLBaseCharacter.h"
#include "../Components/PlayerCharacterMovementComponent.h"
#include "../Components/LedgeDetectorComponent.h"




AFLBaseCharacter::AFLBaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UPlayerCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	/** Movement component's initialization*/
	MyMovementComponent = StaticCast<UPlayerCharacterMovementComponent*>(GetCharacterMovement());

	/** Creation of the LedgeDetectorComponent, in base class */
	LedgeDetectorComponent = CreateDefaultSubobject<ULedgeDetectorComponent>(TEXT("Ledge Detector Component"));
}

void AFLBaseCharacter::Mantle()
{
	FLedgeDescription LedgeDescription;
	if (LedgeDetectorComponent->DetectLedge(LedgeDescription))
	{
		//TODO
	}
}
