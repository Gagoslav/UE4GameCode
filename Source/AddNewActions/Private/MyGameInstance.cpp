// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

FColor UMyGameInstance::ChangeColor()
{
	while (CharacterColor == FColor::Black)
	{
		CharacterColor = FColor::MakeRandomColor();
	}
	return CharacterColor;
}
