// uhuru mccray tutorial sessions


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include <Array.h>
#include <Components/PrimitiveComponent.h>
#include <UObjectBaseUtility.h>

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (DoorTrigger == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Door Trigger not found"), *GetOwner()->GetName())
	}

	if (Owner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Owner not found"), *GetOwner()->GetName())
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//poll the trigger volume
	if(GetTotalMassOfActorsOnPlate() >TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;


	//find all overlapping actors
	if (DoorTrigger == nullptr) { return TotalMass; }
	DoorTrigger->GetOverlappingActors(OUT OverlappingActors);
	
	for (auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//iterate through them adding their mass
		UE_LOG(LogTemp, Warning, TEXT("%s on Door Trigger"), *Actor->GetName());
	}

	return TotalMass;
}