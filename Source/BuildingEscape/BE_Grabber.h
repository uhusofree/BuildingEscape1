// uhuru mccray tutorial sessions

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <Components/InputComponent.h>
#include "BE_Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UBE_Grabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBE_Grabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Reach = 100.f; /**arms length for player pawn can easily be extended for projectiles*/
	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	UInputComponent* InputComponent = nullptr;
	void Grab(); /**Raycast and Attach*/
	void Release();
};
