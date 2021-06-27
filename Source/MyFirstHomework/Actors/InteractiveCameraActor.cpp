// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveCameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

AInteractiveCameraActor::AInteractiveCameraActor()
{
	/**
	* Interactive camera's initialization
	* Camera's space
	* it's extents
	* collision parameters 
	* and hierarchy rules
	*/


	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera Interaction Volume"));
	BoxComponent->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxComponent->SetupAttachment(RootComponent); // we should attach the collision box component to our root component to get ability to move it	
}

void AInteractiveCameraActor::BeginPlay()
{
	/** Calling the necessary functions while overlaping the camera's space*/

	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveCameraActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractiveCameraActor::OnEndOverlap);
}

void AInteractiveCameraActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/** Get the player's controller and pass it's View target to the Camera on begin overlap */

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	FViewTargetTransitionParams TransitionToCameraParams;
	TransitionToCameraParams.BlendTime = TimeForTransitionToCamera;
	PlayerController->SetViewTarget(this, TransitionToCameraParams);
}

void AInteractiveCameraActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/** Get our Pawn Character through the player controller and returns the View Target to it */

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* Character = PlayerController->GetPawn();
	FViewTargetTransitionParams TransitionToPawnParams;
	TransitionToPawnParams.BlendTime = TimeForTransitionToPawn;
	TransitionToPawnParams.bLockOutgoing = true;
	PlayerController->SetViewTarget(Character, TransitionToPawnParams);
}
