// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/UnrealType.h"
#include "Containers/UnrealString.h"
#include "NewBoxComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MABAT_PROJECT_API UNewBoxComponent : public UBoxComponent
{
	GENERATED_BODY()


public:
	UNewBoxComponent();	


protected:
	virtual void BeginPlay() override;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;


};
