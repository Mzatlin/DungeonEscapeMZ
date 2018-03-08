// Copyright 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

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
	BindComponents();

}

void UGrabber::BindComponents() {
	Uphysicshandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Uphysicshandler == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("physics handler is missing from component %s"), *GetOwner()->GetName());
	}
	///Find input component on player
	Uinput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Uinput == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("input handler is missing from component %s"), *GetOwner()->GetName());
	}
	else {
		Uinput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Uinput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	///create linetrace (raycast)
	FHitResult Hit;
	///set up query parameters for the LineTrace 
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); //trace simple instead of complex objects and ignore ourselves 
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetLineReachStart(), GetLineReachEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with: %s"), *(HitActor->GetName()));
	}
	return Hit;
}

void UGrabber::Grab(){
	//try and reach any actors with physics body collision channel set 
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	//if we hit something, attach physics handle 
	if (ActorHit != nullptr) {
		Uphysicshandler->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true); //true allows rotation
	}
}

void UGrabber::Release() {
	//remove physics handle 
	Uphysicshandler->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetFirstPhysicsBodyInReach();

	///DrawDebugLine(GetWorld(), ViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);


	if (Uphysicshandler->GrabbedComponent) { ///if a physics handle is attached, move it
		Uphysicshandler->SetTargetLocation(GetLineReachEnd());
	}

}

FVector UGrabber::GetLineReachEnd() {
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);
	return ViewPointLocation + (ViewPointRotation.Vector() * LineReach);
}

FVector UGrabber::GetLineReachStart()
{
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *ViewPointLocation.ToString(), *ViewPointRotation.ToString());
	return ViewPointLocation;
}

