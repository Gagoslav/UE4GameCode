/**
* The following component is responsible for the correct
* detection of ledges our caracter is available to get on
*/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LedgeDetectorComponent.generated.h"


/** 
* Structure that must describe the climbable ledge (location, rotation) 
* Fields will be modified from the bool DetectLedge(OUT FLedgeDescription& LedgeDescription) function 
*/
USTRUCT (BlueprintType)
struct FLedgeDescription
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ledge Description")
	FVector LedgeLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ledge Description")
	FRotator LedgeRotation;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTHOMEWORK_API ULedgeDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Our main function that has to detect the ledgeg */
	bool DetectLedge(OUT FLedgeDescription& LedgeDescription);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	/** Ledge height properties */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Detection Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float MinimumLedgeHeight = 40.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Detection Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float MaximumLedgeHeight = 200.0f;

	/** Sweep test lenght*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Detection Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float ForwardCheckDistance = 100.0f;

	

private:
	/**
	* Create a pointer to our Character's to get the necessary values from it
	* Must be WeakObjectPtr, to escape the memory leak when the pawn is destroied
	*/
	TWeakObjectPtr <class ACharacter> CachedCharacterOwner;


		
};
