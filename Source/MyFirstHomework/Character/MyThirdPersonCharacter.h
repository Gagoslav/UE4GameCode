// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyThirdPersonCharacter.generated.h"



UENUM(BlueprintType)
enum class EPawnWariant : uint8
{
	Invalid = 0,
	Cube,
	Sphere,
	Triangle
};

UCLASS()
class MYFIRSTHOMEWORK_API AMyThirdPersonCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyThirdPersonCharacter();
	
	UPROPERTY(VisibleAnywhere)
	class UPawnMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SphereRadius = 50.0f;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UArrowComponent* Arrow;
#endif //  WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPawnWariant Variants;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPawnVariants* PropSettings;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetForwardVector() { return ForwardVector; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetRightVector() { return RightVector; }
	

public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float ForwardVector;
	float RightVector;
	
	UFUNCTION()
	void OnBlendComplete();

	AActor* CurrentViewActor;
	

};
