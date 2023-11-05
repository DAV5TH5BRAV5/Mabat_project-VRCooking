// Fill out your copyright notice in the Description page of Project Settings.


#include "Steak.h"

// Sets default values for this component's properties
USteak::USteak()
{

	PrimaryComponentTick.bCanEverTick = true;

	SteakOuterTemperature=20.0f;
	SteakInnerTemperature=20.0f;
	BrowningLevel=0.0f;
}


// Called when the game starts
void USteak::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USteak::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update browning state based on temperature, time, and other factors.
	float k_steak = 0.5f; // Thermal conductivity of the steak (W/m°C)
	float A_steak = 0.01; // Surface area of the steak (in m^2)
	float m_steak = 0.3f; // Mass of the steak (in kg)
	float C_steak = 3.6f; // Specific heat capacity of the steak (J/kg°C)

	// Calculate the heat transfer from the pan to the steak
	float Q_steak_to_steak = (k_steak * A_steak * (SteakOuterTemperature - SteakInnerTemperature) * DeltaTime) / (0.02);

	// Update the steak's temperature
	SteakOuterTemperature -= (Q_steak_to_steak / (C_steak * m_steak));
	SteakInnerTemperature += (Q_steak_to_steak / (C_steak * m_steak));

}

float USteak::GetSteakOuterTemperature() const
{
	return SteakOuterTemperature;
}

void USteak::SetSteakOuterTemperature(float NewSteakOuterTemperature)
{
	SteakOuterTemperature = NewSteakOuterTemperature;
}
float USteak::GetBrowningLevel() const
{
	return BrowningLevel;
}

void USteak::SetBrowningLevel(float NewBrowningLevel)
{
	BrowningLevel = NewBrowningLevel;
}