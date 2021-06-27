// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTPCPawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

void UMyTPCPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisFunction)
{
	
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	Super::TickComponent(DeltaTime, TickType, ThisFunction);
	FVector Direction = GetPendingInputVector().GetClampedToMaxSize(1.0f);
	Velocity = MaxSpeed * Direction;
	FQuat Rotation = UpdatedComponent->GetComponentQuat();
	
	ConsumeInputVector();

	if (bEnableGravity)
	{
		FHitResult HitResult;
		FVector StartPoint = UpdatedComponent->GetComponentLocation();
		float TraceDepth = 1.0f;
		float SphereRadius = 25.0f;
		float LineTraceLenght = SphereRadius + TraceDepth;
		FVector EndPoint = StartPoint - LineTraceLenght * FVector::UpVector;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
		bool bNotFalling = bIsFalling;
		FCollisionShape Sphere = FCollisionShape::MakeSphere(SphereRadius);
		//if nothing is found by the line trace
		bIsFalling = !GetWorld()->SweepSingleByChannel(HitResult, StartPoint, EndPoint, FQuat::Identity, ECollisionChannel::ECC_Visibility, Sphere, CollisionParams);
		if (bIsFalling)
		{
			VerticalVelocity += GetGravityZ() * FVector::UpVector * DeltaTime;
		}
		else if(bNotFalling && VerticalVelocity.Z < 0.0f)
		{
			VerticalVelocity = FVector::ZeroVector;
		}
		
	}
	Velocity += VerticalVelocity;
	FVector DeltaDistance = DeltaTime * Velocity;
	if (!DeltaDistance.IsNearlyZero(1e-6f))
	{
		MoveUpdatedComponent(DeltaDistance, Rotation, true);
		FHitResult Hit(1.f);
		SafeMoveUpdatedComponent(DeltaDistance, Rotation, true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			HandleImpact(Hit, DeltaTime, DeltaDistance);
			// Try to slide the remaining distance along the surface.
			SlideAlongSurface(DeltaDistance, 1.f - Hit.Time, Hit.Normal, Hit, true);
		}
	}
	UpdateComponentVelocity();
}

void UMyTPCPawnMovementComponent::JumpStart()
{
	VerticalVelocity = InitialJumpVelocity * FVector::UpVector;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Jump"));
}

bool UMyTPCPawnMovementComponent::IsFalling() const
{
	return bIsFalling;
}
