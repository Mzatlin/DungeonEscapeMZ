// Copyright 2018

#include "OpenDoor.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();//Find Door
	FRotator FRotation = FRotator(0.f, 90.f, 0.f);//initialize rotator for door
	Owner->SetActorRotation(FRotation); //Set Door rotation

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Poll the trigger volume 
	//If ActorThatOpens is in the volume, then open the door. 
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}


}
