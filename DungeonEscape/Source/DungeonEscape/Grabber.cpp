// Copyright 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	///Find physics handle on player
	Uphysicshandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Uphysicshandler == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("physics handler is missig from component %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *ViewPointLocation.ToString(), *ViewPointRotation.ToString());
	FVector LineTraceEnd = ViewPointLocation + (ViewPointRotation.Vector() * LineReach);
	DrawDebugLine(GetWorld(), ViewPointLocation, LineTraceEnd, FColor(255, 0, 0),false, 0.f,0.f,10.f);

	///create linetrace (raycast)
	FHitResult Hit;
	///set up query parameters for the LineTrace 
	FCollisionQueryParams TraceParameters(FName(TEXT("")),false, GetOwner()); //trace simple instead of complex objects and ignore ourselves 
	GetWorld()->LineTraceSingleByObjectType(OUT Hit,ViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),TraceParameters);
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with: %s"), *(HitActor->GetName()));
	}
	

}

