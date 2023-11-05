// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick=true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
    AActor* Owner=GetOwner();
    Owner->SetActorTickInterval(0.05);
    
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
            // UMaterialInstanceDynamic* MI = UMaterialInstanceDynamic::Create(Actors[i]->FindComponentByClass<UMeshComponent>()->GetMaterial(0),this);
            // MI->SetScalarParameterValue(FName(TEXT("Noise Range Start")), 5);
            //     material->SetVectorParameterValue(FName(TEXT("LightColor")),FLinearColor(0.0,0.0,0.0,1.0);
            float checker;
            material->GetScalarParameterValue(FName(TEXT("Noise Range Start")), checker);
            if(checker<=0.860372f)
            {
                // Calculated Noise Starter, Noise Ender per tick interval
                float CalculationStartPerTickInterval = 0.0021475f;
                float CalculationEndPerTickInterval = 0.0026595f;
                float CalculationTilingPerTickInterval = 0.000000170667f;

                // Current Noise Starter, Noise Ender
                float CurrentStart;
                float CurrentEnd;
                float CurrentTiling;
                material->GetScalarParameterValue(FName(TEXT("Noise Range Start")), CurrentStart);
                material->GetScalarParameterValue(FName(TEXT("Noise Range End")), CurrentEnd);
                material->GetScalarParameterValue(FName(TEXT("Tiling")), CurrentTiling);

                // Finale Calculations :-)
                float CalculationStart = CurrentStart + CalculationStartPerTickInterval;
                float CalculationEnd = CurrentEnd + CalculationEndPerTickInterval;
                float CalculationTiling = CurrentTiling + CalculationTilingPerTickInterval;
                
                // Setting finale Calculations in Steak Material
                material->SetScalarParameterValue(FName(TEXT("Noise Range Start")), CalculationStart);
                material->SetScalarParameterValue(FName(TEXT("Noise Range End")), CalculationEnd);
                material->SetScalarParameterValue(FName(TEXT("Tiling")), CalculationTiling);

            }
            else
            {
                // Calculated Tiling, Noise Starter, Noise Ender per tick interval
                float CalculationTilingPerTickInterval = 0.000000170667f;
                float CalculationStartPerTickInterval = 0.0000516075f;
                float CalculationEndPerTickInterval = 0.00000533447f;

                // Current Tiling, Noise Starter, Noise Ender
                float CurrentTiling;
                float CurrentStart;
                float CurrentEnd;
                material->GetScalarParameterValue(FName(TEXT("Tiling")), CurrentTiling);
                material->GetScalarParameterValue(FName(TEXT("Noise Range Start")), CurrentStart);
                material->GetScalarParameterValue(FName(TEXT("Noise Range End")), CurrentEnd);

                // Finale Calculations :-)
                float CalculationTiling = CurrentTiling + CalculationTilingPerTickInterval;
                float CalculationStart = CurrentStart + CalculationStartPerTickInterval;
                float CalculationEnd = CurrentEnd + CalculationEndPerTickInterval;

                // Setting finale Calculations in Steak Material
                material->SetScalarParameterValue(FName(TEXT("Tiling")), CalculationTiling);
                material->SetScalarParameterValue(FName(TEXT("Noise Range Start")), CalculationStart);
                material->SetScalarParameterValue(FName(TEXT("Noise Range End")), CalculationEnd);

                        //if(!(Actors[i]->FindComponentByClass<UMeshComponent>()->GetMaterial(0)->GetName()).Equals("MaterialInstanceDynamic_1"))
                //{
                //    Actors[i]->FindComponentByClass<UMeshComponent>()->SetMaterial(0,MI);
                //}
            }
            
        }
    }
}