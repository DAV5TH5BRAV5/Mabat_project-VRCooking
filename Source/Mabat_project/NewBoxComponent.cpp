// Fill out your copyright notice in the Description page of Project Settings.


#include "NewBoxComponent.h"

UNewBoxComponent::UNewBoxComponent()
{
    PrimaryComponentTick.bCanEverTick=true;
}

void UNewBoxComponent::BeginPlay()
{
    Super::BeginPlay();
    AActor* Owner=GetOwner();
    Owner->SetActorTickInterval(0.05);
    
}

void UNewBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for(int32 i=0;i<Actors.Num();i++){
        if(Actors[i]->ActorHasTag(AcceptableActorTag)){
            UStaticMeshComponent* meshI = Actors[i]->FindComponentByClass<UStaticMeshComponent>();
            //     UE_LOG(LogTemp, Display, TEXT("OverLapping %s"), *(meshI->GetName()));
            //UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(meshI->GetMaterial(0), Actors[i]);
            UMaterialInstanceDynamic* material;
            material=meshI->CreateAndSetMaterialInstanceDynamicFromMaterial(0, (meshI->GetMaterial(0)));
            float CookingProgress;
            float CookingRate;
            material->GetScalarParameterValue(FName(TEXT("CookingProgress")), CookingProgress);
            material->GetScalarParameterValue(FName(TEXT("CookingRate")), CookingRate);
            CookingProgress += CookingRate * DeltaTime;
            CookingProgress = FMath::Clamp(CookingProgress, 0.0f, 1.0f);

            // Modify material properties based on the cooking progress
            material->SetScalarParameterValue(FName(TEXT("CookingProgress")), CookingProgress);
            
        }
            
        
    }
}



