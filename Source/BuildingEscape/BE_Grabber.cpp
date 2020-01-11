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

	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	/*GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("location: %s, rotation: %s"), *PlayerViewLocation.ToString(), *PlayerViewRotation.ToString()));
UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewLocation.ToString(), *PlayerViewRotation.ToString())*/

	FVector LineTraceEnd = PlayerViewLocation + FVector(0.f, 0.f, 50.f);

	DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEnd, FColor(0, 30, 155), false, -1, 0, 12.333);
}

