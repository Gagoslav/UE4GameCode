// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FLBaseCharacter.h"
#include "Components/TimelineComponent.h"
#include "MyFLCharacter.generated.h"


/**
 * Main Player Character's class
 * inherited from the AFLBaseCharacter
 * contains also the implementations of previously declared pure virtual methods
 */
UCLASS(Blueprintable)
class MYFIRSTHOMEWORK_API AMyFLCharacter : public AFLBaseCharacter
{
	GENERATED_BODY()
public:
	AMyFLCharacter(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE bool GetIsCrouching() { return bIsCrouched; }
	
	
protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyFLCharacter | Settings")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyFLCharacter | Settings")
	class UCameraComponent* Camera;

	/** Curve necessary for the SprintTimeline implementation (pointer)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline Curve")
	UCurveFloat* SprintCurve;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void MoveForward(float Value) override;

	virtual void MoveRight(float Value) override;

	virtual void LookUp(float Value) override;

	virtual void Turn(float Value) override;

	virtual void ChangeCrouchState() override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual bool CanJumpInternal_Implementation() const override;
	virtual void OnJumped_Implementation() override;

	virtual void StartSprint() override;
	virtual void StopSprint() override;

	/** Declaring and initial implementation of events, called while character is sprinting */
	UFUNCTION(BlueprintNativeEvent)
	void OnStartSprint();
	virtual void OnStartSprint_Implementation();

	/** Declaring and initial implementation of events, called while character is sprinting */
	UFUNCTION(BlueprintNativeEvent)
	void OnEndSprint();
	virtual void OnEndSprint_Implementation();

	virtual void SwimForward(float Value) override;
	virtual void SwimRight(float Value) override;
	virtual void SwimUp(float Value) override;

	/** Function interacting with the FTimeline::AddInterpFloat through the FOnTimelineFloat Structure*/
	UFUNCTION()
	void UpdateSprintTimeline(float Value);

private:
	bool bIsCrouched = false;
	float DefaultWalkSpeed = 0.0f;
	FTimeline SprintTimeline;
	
};
