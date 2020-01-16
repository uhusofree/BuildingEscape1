// uhuru mccray tutorial sessions

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetTotalMassOfActorOnPlate();
private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.f;


	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorTrigger;	

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;
		float LastDoorOpenTime;
		float LastCloseDoorTime;

		AActor* ActorThatOpens;
		AActor* Owner;
	
};
