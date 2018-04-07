// Copyright 2018

#pragma once
#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called when the game starts
protected:
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	///returns total mass in kg
	float GetTotalMassOfActorsOnPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
   //macro that will make the openangle viewable in properties windows and can be edited 
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;
	UPROPERTY(EditAnywhere) 
	ATriggerVolume* PressurePlate = nullptr;
	
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;

	//the owning door
	AActor* Owner = nullptr; 
};
