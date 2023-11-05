// Fill out your copyright notice in the Description page of Project Settings.


#include "Stove.h"

// Sets default values for this component's properties
UStove::UStove()
{

	PrimaryComponentTick.bCanEverTick = true;
    StoveSetTemperature = 175.0f; // Set default stove temperature
}


// Called when the game starts
void UStove::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

float UStove::GetStoveSetTemperature() const
{
    return StoveSetTemperature;
}