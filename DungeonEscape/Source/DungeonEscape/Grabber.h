// Copyright 2018

#pragma once
#include "PhysicsEngine/PhysicsHandleComponent.h"	
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	///returns current end of reach line 
	FVector GetLineReachEnd();

	///returns current start of reach line 
	FVector GetLineReachStart();

private:
	float LineReach = 100.f;
		
	UPhysicsHandleComponent* Uphysicshandler = nullptr;
	UInputComponent* Uinput = nullptr;
	///raycast and grab objects that are in reach 
	void Grab();
	///called when grab is released
	void Release();
	void BindComponents();

	const FHitResult GetFirstPhysicsBodyInReach();
};
