// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "InteractiveCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTHOMEWORK_API AInteractiveCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	
	/** Interactive camera actor's components initialization */
	AInteractiveCameraActor();
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

	
	/** Necessary parameters for the transition from one View target to another */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeForTransitionToCamera = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeForTransitionToPawn = 1.0f;

	/** Delegates responsible for generating the overlap events, according to whom the logic will work */
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
