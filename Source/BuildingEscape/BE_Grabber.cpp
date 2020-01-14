// uhuru mccray tutorial sessions



#include "Engine/World.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include <Components/ActorComponent.h>
#include "GameFramework/Actor.h"
//#include "Runtime/Core/Public/Math/Vector.h"
#include "GameFramework/PlayerController.h"
#include <LogMacros.h>
#include "BE_Grabber.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>

// compile test
// compile test2

#define OUT //does nothing but helps with getplayerviewpoint out parameters 

// Sets default values for this component's properties
UBE_Grabber::UBE_Grabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBE_Grabber::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	//UE_LOG(LogTemp, Warning, TEXT("Grabber Working"));

	FindPhysicsHandleComponent();
	InputHandler();

}


// Called every frame
void UBE_Grabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);  //Getting PlayersView point/Rotation in the world

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	if (PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->SetTargetLocation(LineTraceEnd);
	}
	//if find and hold something is in hold it and move with it
}

void UBE_Grabber::FindPhysicsHandleComponent()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandler)
	{
		UE_LOG(LogTemp, Error, TEXT("%s not foud"), *GetOwner()->GetName());
	}
	else
	{
		//PhysicsHandler is found
	}
}

void UBE_Grabber::InputHandler()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s not found"), *GetOwner()->GetName());
	}
	else
	{

		//InputComponent is found
		InputComponent->BindAction("Grab", IE_Pressed, this, &UBE_Grabber::Grab);
		InputComponent->BindAction("Grab Release", IE_Released, this, &UBE_Grabber::Release);
	}
}

FHitResult UBE_Grabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);  //Getting PlayersView point/Rotation in the world

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 30, 155), false, 0, 0, 2.f);

	///linetracesingle and followed parameters in description created names to pass in as params
	FHitResult Hit;
	FCollisionObjectQueryParams HitParamObject(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, HitParamObject, TraceParameters);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTraceHitresult: %s"), (*ActorHit->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, .5, FColor::Blue, FString::Printf(TEXT("Hit Results: %s"), (*ActorHit->GetName())));
	}

	return Hit;
}

void UBE_Grabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed Pressed"));
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	//Attached Physics Handler
	if (ActorHit != nullptr)
	{
		PhysicsHandler->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
	//try reach actor with collision channel set
	//if we hit something then attach

}

void UBE_Grabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed Released"));
	PhysicsHandler->ReleaseComponent();
	//TODO release physics handle
}

