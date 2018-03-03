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
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *ViewPointLocation.ToString(), *ViewPointRotation.ToString());
	FVector LineTraceEnd = ViewPointLocation + (ViewPointRotation.Vector() * LineReach);
	DrawDebugLine(GetWorld(), ViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	///create linetrace (raycast)
	FHitResult Hit;
	///set up query parameters for the LineTrace 
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); //trace simple instead of complex objects and ignore ourselves 
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with: %s"), *(HitActor->GetName()));
	}
	return FHitResult();
}

void UGrabber::Grab(){
	UE_LOG(LogTemp, Warning, TEXT("Grab!"));
	//try and reach any actors with physics body collision channel set 

	//if we hit something, attach physics handle 
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release!"));

	//remove physics handle 
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetFirstPhysicsBodyInReach();
	

}

