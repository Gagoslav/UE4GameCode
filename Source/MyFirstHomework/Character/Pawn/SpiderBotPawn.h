// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyThirdPersonCharacter.h"
#include "SpiderBotPawn.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API ASpiderBotPawn : public AMyThirdPersonCharacter
{
	GENERATED_BODY()

public:
	ASpiderBotPawn();

	virtual void Tick(float DeltaSeconds) override;



	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetFrontRightLegOffset() { return FrontRightLegOffset; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetFrontLeftLegOffset() { return FrontLeftLegOffset; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetRareRightLegOffset() { return RareRightLegOffset; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetRareLeftLegOffset() { return RareLeftLegOffset; }

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	class USkeletalMeshComponent* SkeletalMesh;

	float GetSocketOffset(FName SocketName);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpiderBot| IK settings", meta = (ClampMin = 0.0f, UMin = 0.0f))
	float MaxEnd = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spider bot sockets")
	FName FrontRightLegSoccet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spider bot sockets")
	FName FrontLeftLegSoccet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spider bot sockets")
	FName RareRightLegSoccet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spider bot sockets")
	FName RareLeftLegSoccet;

private:

	float FrontRightLegOffset = 0.0f;
	float FrontLeftLegOffset = 0.0f;
	float RareRightLegOffset = 0.0f;
	float RareLeftLegOffset = 0.0f;

	float LineTraceLenght = 0.0f;
	float LineTraceScale = 0.0f;

};
