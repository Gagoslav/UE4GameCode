// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderBotPawn.h"
#include "Kismet/KismetSystemLibrary.h"


ASpiderBotPawn::ASpiderBotPawn()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spider bot skeletal mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	LineTraceScale = GetActorScale3D().Z;
	LineTraceLenght = AMyThirdPersonCharacter::SphereRadius * LineTraceScale;

}

void ASpiderBotPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FrontRightLegOffset = GetSocketOffset(FrontRightLegSoccet);
	FrontLeftLegOffset = GetSocketOffset(FrontLeftLegSoccet);
	RareRightLegOffset = GetSocketOffset(RareRightLegSoccet);
	RareLeftLegOffset = GetSocketOffset(RareLeftLegSoccet);
}

float ASpiderBotPawn::GetSocketOffset(FName SocketName)
{
	float Result = 0.0f;
	FVector SocketLocation = SkeletalMesh->GetSocketLocation(SocketName);
	FVector Start (SocketLocation.X, SocketLocation.Y, GetActorLocation().Z);
	FVector End = Start - LineTraceLenght * FVector::UpVector;
	FHitResult HitResult;
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceType, true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, HitResult, true))
	{
		Result = (End.Z - HitResult.Location.Z)/LineTraceScale;
		
	}
	else if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), End, End- MaxEnd * FVector::UpVector, TraceType, true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, HitResult, true))
	{
		Result =  (End.Z - HitResult.Location.Z)/LineTraceScale;
	}

	return Result;
}
