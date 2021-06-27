// Fill out your copyright notice in the Description page of Project Settings.


#include "MyThirdPersonCharacter.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "../Components/MyTPCPawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyThirdPersonCharacter::AMyThirdPersonCharacter()
{

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->SetSphereRadius(SphereRadius);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CollisionComponent;

	//MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("Movement component"));
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UMyTPCPawnMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = 1;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CurrentViewActor = CameraManager->GetViewTarget();
	CameraManager->OnBlendComplete().AddUFunction(this, FName("OnBlendComplete"));
}


// Called to bind functionality to input
void AMyThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyThirdPersonCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMyThirdPersonCharacter::Jump);
}

void AMyThirdPersonCharacter::MoveForward(float Value)
{
	ForwardVector = Value;
	if (Value != 0.0f)
	{
		AddMovementInput(CurrentViewActor->GetActorForwardVector(), Value);
	}
}

void AMyThirdPersonCharacter::MoveRight(float Value)
{
	RightVector = Value;
	if (Value != 0.0f)  
	{
		AddMovementInput(CurrentViewActor->GetActorRightVector(), Value);
	}
}

void AMyThirdPersonCharacter::Jump()
{
	checkf(MovementComponent->IsA< UMyTPCPawnMovementComponent>(), TEXT("Jump can work only with UMyTPCPawnMovementComponent"));
	UMyTPCPawnMovementComponent* BaseMovement = StaticCast<UMyTPCPawnMovementComponent*>(MovementComponent);
	BaseMovement->JumpStart();
}

void AMyThirdPersonCharacter::OnBlendComplete()
{
	CurrentViewActor = GetController()->GetViewTarget();
}

