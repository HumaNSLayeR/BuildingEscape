// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenBullCowGame.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT
// Sets default values for this component's properties
UOpenBullCowGame::UOpenBullCowGame()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOpenBullCowGame::BeginPlay()
{
	Super::BeginPlay();
	ActorThatTriggers = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PressurePlate) { return; }
	Owner = GetOwner();
	PressurePlate->OnActorBeginOverlap.AddUniqueDynamic(this, &UOpenBullCowGame::OnPressurePlateBeginOverlap);
	
}

// Called every frame
void UOpenBullCowGame::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UOpenBullCowGame::OnPressurePlateBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor == ActorThatTriggers)
	{

		FPlatformProcess::CreateProc(TEXT("C:\\Users\\akgan\\source\\repos\\UnrealCourse\\Section_02\\Debug\\BullCowGame.exe"), nullptr, true, false, false, nullptr, 0, nullptr, nullptr);
	}
	return;
}
