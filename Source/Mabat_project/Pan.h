// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h" // Include the SphereComponent header
#include "Components/SceneComponent.h"
#include "Pan.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MABAT_PROJECT_API UPan : public UActorComponent
{
	GENERATED_BODY()

public:
    UPan();

protected:
    virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(VisibleAnywhere, Category = "Cooking")
    class USphereComponent* PanCollisionComponent; // Use a sphere component for collision detection

    UPROPERTY(EditAnywhere, Category = "Cooking")
    float PanTemperature; // Temperature of the pan
    
	UPROPERTY(EditAnywhere, Category = "Cooking")
    float StoveHeatTransferCoefficient; // Heat transfer coefficient

	UPROPERTY(EditAnywhere, Category = "Cooking")
    float PanHeatCapacity; // heat capacity

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTagStove;	

	UPROPERTY(EditAnywhere)
	FName AcceptableActorTagSteak;
};
