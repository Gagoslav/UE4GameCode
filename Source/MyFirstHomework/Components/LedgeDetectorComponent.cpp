
#include "LedgeDetectorComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameCodeTypes.h"
#include "DrawDebugHelpers.h"


void ULedgeDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	/** On begin play initialize our WeakObjectPtr to our character */
	checkf(GetOwner()->IsA<ACharacter>(), TEXT("ULedgeDetectorComponent::BeginPlay() only a character can use ULedgeDetector"));
	CachedCharacterOwner = StaticCast <ACharacter*>(GetOwner());
	
}

bool ULedgeDetectorComponent::DetectLedge(OUT FLedgeDescription& LedgeDescription)
{
	/** Get our character's cached capsule component */
	UCapsuleComponent* CapsuleComponent = CachedCharacterOwner->GetCapsuleComponent();

	/** Make a query params for the sweep and overlap tests*/
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.AddIgnoredActor(GetOwner());
	
	/** We add some additional space for the definition of the character's bottom */
	float BottomZOffset = 2.0f;
	FVector CharacterBottom = CachedCharacterOwner->GetActorLocation() - (CapsuleComponent->GetScaledCapsuleHalfHeight() - BottomZOffset) * FVector::UpVector;

	
	/** 1. Forward Check */

	/** Here we define our Sweep test capsule parameters */
	float ForwardCheckCapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius(); // the future depth of sweep test
	float ForwardCheckCapsuleHalfHeight = (MaximumLedgeHeight - MinimumLedgeHeight) / 2;
	
	/** Create a components necessary for a sweep test*/
	FHitResult ForwardCheckHitResult;
	FCollisionShape ForwardCapslueShape = FCollisionShape::MakeCapsule(ForwardCheckCapsuleRadius, ForwardCheckCapsuleHalfHeight);
	
	/** Define capsule sweep test's position*/
	FVector ForwardStartLocation = CharacterBottom + (MinimumLedgeHeight + ForwardCheckCapsuleHalfHeight) * FVector::UpVector;
	FVector ForwardEndLocation = ForwardStartLocation + CachedCharacterOwner->GetActorForwardVector() * ForwardCheckDistance;
	float DrawDebugTime = 3.0f;

	DrawDebugCapsule(GetWorld(), ForwardStartLocation, CapsuleComponent->GetScaledCapsuleHalfHeight(), CapsuleComponent->GetScaledCapsuleRadius(), FQuat::Identity, FColor::Black, false, DrawDebugTime);
	DrawDebugCapsule(GetWorld(), ForwardEndLocation, CapsuleComponent->GetScaledCapsuleHalfHeight(), CapsuleComponent->GetScaledCapsuleRadius(), FQuat::Identity, FColor::Black, false, DrawDebugTime);
	DrawDebugLine(GetWorld(), ForwardStartLocation, ForwardEndLocation, FColor::Black, false, DrawDebugTime);

	if (!GetWorld()->SweepSingleByChannel(ForwardCheckHitResult, ForwardStartLocation, ForwardEndLocation, FQuat::Identity, ECC_Climbing, ForwardCapslueShape, QueryParams))
	{
		return false;
	}
	DrawDebugCapsule(GetWorld(), ForwardCheckHitResult.Location, CapsuleComponent->GetScaledCapsuleHalfHeight(), CapsuleComponent->GetScaledCapsuleRadius(), FQuat::Identity, FColor::Red, false, DrawDebugTime);
	DrawDebugPoint(GetWorld(), ForwardCheckHitResult.ImpactPoint, 20.0f, FColor::Purple, false, DrawDebugTime);
	/** 2. Downward Check */

	/** Create a components necessary for a sweep test*/
	FHitResult DownwardCheckHitResult;

	/** Here we define our Sweep test sphere parameters */
	float DownwardSphereCheckRadius = CapsuleComponent->GetScaledCapsuleRadius();
	FCollisionShape DownwardSphereShape = FCollisionShape::MakeSphere(DownwardSphereCheckRadius);

	/** Determine the depth the character not to be placed on the edge of the ledge*/
	float DownwardCheckDepthOffset = 10.0f;

	/** Define sphere sweep test's position*/
	FVector DownwardStartLocation = ForwardCheckHitResult.ImpactPoint - ForwardCheckHitResult.ImpactNormal * DownwardCheckDepthOffset;
	DownwardStartLocation.Z = CharacterBottom.Z + MaximumLedgeHeight + DownwardSphereCheckRadius;
	FVector DownwardEndLocation(DownwardStartLocation.X, DownwardStartLocation.Y, CharacterBottom.Z);
	
	if (!GetWorld()->SweepSingleByChannel(DownwardCheckHitResult, DownwardStartLocation, DownwardEndLocation, FQuat::Identity, ECC_Climbing, DownwardSphereShape, QueryParams))
	{
		return false;
	}

	FVector DrawDebugSphereLocation = DownwardCheckHitResult.Location;
	DrawDebugSphere(GetWorld(), DrawDebugSphereLocation, DownwardSphereCheckRadius, 32, FColor::Red, false, DrawDebugTime);
	/** 3. Overlap Check (is necessary to understand if a character can step on the ledge) */

	/** Create a components necessary for a overlap test by profile*/
	float OverlapCapsuleRadius = CapsuleComponent->GetScaledCapsuleRadius();
	float OverlapCapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	FCollisionShape OverlapCapsuleShape = FCollisionShape::MakeCapsule(OverlapCapsuleRadius, OverlapCapsuleHalfHeight);
	FVector OverlapLocation = DownwardCheckHitResult.ImpactPoint + OverlapCapsuleHalfHeight * FVector::UpVector;
	if (GetWorld()->OverlapAnyTestByProfile(OverlapLocation, FQuat::Identity, FName("Pawn"), OverlapCapsuleShape, QueryParams))
	{
		DrawDebugCapsule(GetWorld(), OverlapLocation, OverlapCapsuleHalfHeight, OverlapCapsuleRadius, FQuat::Identity, FColor::Yellow, false, DrawDebugTime);
		return false;
	}


	/** As our function has params passed by reference, here me modify these params */
	LedgeDescription.LedgeLocation = DownwardCheckHitResult.ImpactPoint;
	LedgeDescription.LedgeRotation = (ForwardCheckHitResult.ImpactNormal * FVector(-1.0f, -1.0f, 0.0f)).ToOrientationRotator();

	/** return true if all tests pass well */
	return true;
}
