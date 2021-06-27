// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PawnVariants.generated.h"

USTRUCT(BlueprintType)
struct FPawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Visual Parameter")
	UStaticMesh* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Visual Parameter")
	FTransform Transform;
};

enum class EPawnWariant;

UCLASS()
class MYFIRSTHOMEWORK_API UPawnVariants : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EPawnWariant, FPawnParams> VariantOfPawn;
	
};
