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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//UPROPERTY(VisableAnywhere) //macro that will make the openangle viewable in properties windows but can't be edited 
	float OpenAngle = 90.f;
	UPROPERTY(EditAnywhere) 
	ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
    AActor* ActorThatOpens; //reminder that pawn inherits from actor 
	
};
