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
	if (PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->SetTargetLocation(GetReachLineEnd());
	}
	//if find and hold something is in hold it and move with it
}

void UBE_Grabber::FindPhysicsHandleComponent()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s not foud"), *GetOwner()->GetName());
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
		InputComponent->BindAction("Grab", IE_Pressed, this, &UBE_Grabber::Grab);
		InputComponent->BindAction("Grab Release", IE_Released, this, &UBE_Grabber::Release);
	}
}

FHitResult UBE_Grabber::GetFirstPhysicsBodyInReach() const
{
	///linetracesingle and followed parameters in description created names to pass in as params
	FHitResult Hit;
	FCollisionObjectQueryParams HitParamObject(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetReachLineStart(), GetReachLineEnd(), HitParamObject, TraceParameters);

	DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(), FColor(0, 30, 155), false, 0, 0, 2.f);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTraceHitresult: %s"), (*ActorHit->GetName()));

	}
	return Hit;
}

void UBE_Grabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed Pressed"));
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); //gets the mesh 
	auto ActorHit = HitResult.GetActor();

	//Attached Physics Handler
	if (ActorHit != nullptr)
	{
		PhysicsHandler->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	} //try reach actor with collision channel set
}

void UBE_Grabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed Released"));
	PhysicsHandler->ReleaseComponent();
}

FVector UBE_Grabber::GetReachLineStart() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); 

	return PlayerViewPointLocation;
}

FVector UBE_Grabber::GetReachLineEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);  //Getting PlayersView point/Rotation in the world

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}