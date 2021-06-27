// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformLift.h"

// Sets default values
APlatformLift::APlatformLift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* DefaultPlatformRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Platform root"));
	RootComponent = DefaultPlatformRoot;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	PlatformMesh->SetupAttachment(DefaultPlatformRoot);
	
}

// Called when the game starts or when spawned
void APlatformLift::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = PlatformMesh->GetRelativeLocation();
	SelectOption();
}


void APlatformLift::SelectOption()
{
	if (PlatformBehavior == EBehavior::Loop)
	{
		bLoopOption = true;
	}
	else
	{
		bLoopOption = false;
	}
}

// Called every frame
void APlatformLift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

