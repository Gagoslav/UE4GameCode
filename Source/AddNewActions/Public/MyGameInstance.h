// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEWACTIONSADDITION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	FColor ChangeColor();

private:
	FColor CharacterColor = FColor::Black;
	

};
