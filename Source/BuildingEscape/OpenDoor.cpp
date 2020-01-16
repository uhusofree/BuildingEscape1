// uhuru mccray tutorial sessions


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include <LogMacros.h>
#include <Components/PrimitiveComponent.h>

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	/*Rotation.Add(0.f, MyNumber, 0.f);*/
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor()
{

	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor:: CloseDoor()
{

	Owner->SetActorRotation(FRotator(0.f,0.f,0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetTotalMassOfActorOnPlate() > 50.f) //TODO make float into a parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}

	
	// ...
}

float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	//find all the overlapping actors
	DoorTrigger->GetOverlappingActors(OUT OverlappingActors);
	//iterate though them adding their masses
	for (auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on trigger"), *Actor->GetName());
	}

	return TotalMass;
}
