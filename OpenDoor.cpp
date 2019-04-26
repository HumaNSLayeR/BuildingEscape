// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT
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
	if ((PressurePlate) == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing PressurePlate!"), *GetOwner()->GetName())
	}
	Owner = GetOwner();
	if ((Owner) == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing Owner!"), *GetOwner()->GetName())
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Pool the Trigger Volume
	if (GetTotalMassOfActorsOnPlane() > TriggerMass) 
	{
		OnOpen.Broadcast();
	}

	// Check if it's time to close the door
	else
	{
		OnClose.Broadcast();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlane() 
{
	float TotalMass = 0.f;

	//Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	//Iterate through them adding their masses
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
	
	}
	return TotalMass;
}
