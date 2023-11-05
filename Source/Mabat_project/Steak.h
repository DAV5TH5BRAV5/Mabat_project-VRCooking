// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Steak.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MABAT_PROJECT_API USteak : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USteak();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Cooking")
    float SteakOuterTemperature; // heat capacity

	UPROPERTY(EditAnywhere, Category = "Cooking")
    float SteakInnerTemperature; // heat capacity
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BrowningLevel;
	
	UFUNCTION(BlueprintCallable, Category = "Cooking")
    float GetSteakOuterTemperature() const;

	UFUNCTION(BlueprintCallable, Category = "Cooking")
    void SetSteakOuterTemperature(float NewSteakOuterTemperature);

	UFUNCTION(BlueprintCallable, Category = "Cooking")
    float GetBrowningLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Cooking")
    void SetBrowningLevel(float NewBrowningLevel);
};
