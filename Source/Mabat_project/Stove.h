// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MABAT_PROJECT_API UStove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStove();

    UPROPERTY(EditAnywhere, Category = "Cooking")
    float StoveSetTemperature; // Set temperature for the stove

    // Function to provide heat transfer information to the pan.
    UFUNCTION(BlueprintCallable, Category = "Cooking")
    float GetStoveSetTemperature() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
