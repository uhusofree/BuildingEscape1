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
}


// Called every frame
void UBE_Grabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);  //Getting PlayersView point/Rotation in the world

	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("location: %s, rotation: %s"), *PlayerViewLocation.ToString(), *PlayerViewRotation.ToString()));
UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewLocation.ToString(), *PlayerViewRotation.ToString())*/

	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 30, 155), false, 0, 0, 2.f);

	/*UE_LOG(LogTemp, Warning, TEXT("linetraceend: %s n/PlayerViewPointLocation: %s"), *LineTraceEnd.ToString(), *PlayerViewPointLocation.ToString());
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, FString::Printf(TEXT("LineTraceEnd: %s n/PlayerviewPointlocation: %s"), *LineTraceEnd.ToString(), *PlayerViewPointLocation.ToString()));*/

	///linetracesingle and followed parameters in description created names to pass in as params
	FHitResult Hit;
	FCollisionObjectQueryParams HitParamObject(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, HitParamObject, TraceParameters);
	
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTraceHitresult: %s"), (*ActorHit->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, .5, FColor:: Blue, FString::Printf(TEXT("Hit Results: %s"), (*ActorHit->GetName())));
	}
	
	

}

