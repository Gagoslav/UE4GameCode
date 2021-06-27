// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformLift.generated.h"



UENUM()
enum class EBehavior : uint8
{
	OnDemand = 0,
	Loop
};


UCLASS()
class MYFIRSTHOMEWORK_API APlatformLift : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformLift();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (MakeEditWidget))
	FVector EndPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	FVector StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBehavior PlatformBehavior = EBehavior::OnDemand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoopOption = false;

	void SelectOption();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
