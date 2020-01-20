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
}


// Called when the game starts
void UBE_Grabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	InputHandler();
}


// Called every frame
void UBE_Grabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->SetTargetLocation(GetReachLineEnd()); //pick up object and move
	}
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


void UBE_Grabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed Pressed"));
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	//Attached Physics Handler
	if (ActorHit != nullptr)
	{
		PhysicsHandler->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
	}
}

void UBE_Grabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed Released"));
	PhysicsHandler->ReleaseComponent();
}

FHitResult UBE_Grabber::GetFirstPhysicsBodyInReach()
{
	//Traces out a line into and checks for a hit
	DrawDebugLine(GetWorld(), GetReachLineBegin(), GetReachLineEnd(), FColor(0, 30, 155), false, 0, 0, 2.f);

	FHitResult Hit;
	FCollisionObjectQueryParams HitParamObject(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetReachLineBegin(), GetReachLineEnd(), HitParamObject, TraceParameters);

	return Hit;
}

FVector UBE_Grabber::GetReachLineBegin()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); 

	return PlayerViewPointLocation;
}

FVector UBE_Grabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);  //Getting PlayersView point/Rotation in the world

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
