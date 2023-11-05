// Fill out your copyright notice in the Description page of Project Settings.


#include "Pan.h"
#include "Stove.h" // Include the Stove class header
#include "Steak.h" // Include the Steak class header

// Sets default values for this component's properties
UPan::UPan()
{
	PrimaryComponentTick.bCanEverTick = true;
    // Create and attach the USphereComponent
    PanCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PanCollisionComponent"));

    // Set up collision settings for the sphere component as needed
    PanCollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic")); 
    PanCollisionComponent->InitSphereRadius(50.0f);
    if (AActor* OwnerActor = GetOwner())
    {
        UStaticMeshComponent* MeshComponent = OwnerActor->FindComponentByClass<UStaticMeshComponent>();

        if (MeshComponent)
        {
			FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
            PanCollisionComponent->AttachToComponent(OwnerActor->GetRootComponent(), AttachRules);
		}
    }

    // Initialize pan temperature and browning
    PanTemperature = 20.0f; // Initial pan temperature in Celsius
	StoveHeatTransferCoefficient = 200.0f; // Default heat transfer coefficient
	PanHeatCapacity=900.0f;
	AcceptableActorTagStove="Stove";
	AcceptableActorTagSteak="Steak";
}


// Called when the game starts
void UPan::BeginPlay()
{
	Super::BeginPlay();


	
}


// Called every frame
void UPan::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
    TArray<AActor*> Actors;
	PanCollisionComponent->GetOverlappingActors(Actors, AActor::StaticClass());
	bool isOvenFound=false;
	for(int32 i=0;i<Actors.Num();i++){
        if(Actors[i]->ActorHasTag(AcceptableActorTagStove)){
			isOvenFound=true;
		}
	}
	for(int32 i=0;i<Actors.Num();i++){
        if(isOvenFound && Actors[i]->ActorHasTag(AcceptableActorTagStove)){
			// Update PanTemperature based on heat transfer, stove temperature, etc.
        	UStove* stove = Actors[i]->FindComponentByClass<UStove>();
    		float HeatTransfer = StoveHeatTransferCoefficient * 0.01 * (stove->GetStoveSetTemperature() - PanTemperature);
    		float PanCalc = HeatTransfer/(0.3 * PanHeatCapacity); // Assuming steak is 300gr
			PanTemperature += DeltaTime * PanCalc;

		}
		else if(!isOvenFound)
		{
			// Update PanTemperature based on heat transfer, stove temperature, etc.
    		float HeatTransfer = StoveHeatTransferCoefficient * 0.01 * (20 - PanTemperature);
    		float PanCalc = HeatTransfer/(0.3 * PanHeatCapacity); // Assuming steak is 300gr
			PanTemperature += DeltaTime * PanCalc;

		}
		else if(Actors[i]->ActorHasTag(AcceptableActorTagSteak))
		{
			// Update browning state based on temperature, time, and other factors.
			float k_steak = 0.5f; // Thermal conductivity of the steak (W/m°C)
			float A_steak = 0.025f; // Surface area of the steak (in m^2)
			float m_steak = 0.3f; // Mass of the steak (in kg)
			float C_steak = 3.6f; // Specific heat capacity of the steak (J/kg°C)
        	USteak* steak = Actors[i]->FindComponentByClass<USteak>();
			// Calculate the heat transfer from the pan to the steak
			float Q_pan_to_steak = (k_steak * A_steak * 0.40 * (PanTemperature - steak->GetSteakOuterTemperature()) * DeltaTime) / (m_steak * C_steak);

			// Update the steak's temperature
			steak->SetSteakOuterTemperature((steak->GetSteakOuterTemperature() + Q_pan_to_steak / (m_steak * C_steak)) );

			float SlowdownFactor = 0.001f;  
			float TemperatureDifference = PanTemperature - steak->GetSteakOuterTemperature();
			float InitialBrowningRate = 0.001f; // Initial browning rate
			float MaximumBrowningRate = 0.01f; // Maximum browning rate
			float SigmoidSlope = 0.5f; 

			// Calculate a slowdown factor based on the temperature difference
			float BrowningRate = InitialBrowningRate + (MaximumBrowningRate - InitialBrowningRate) / (1.0f + FMath::Exp(-SigmoidSlope * steak->GetBrowningLevel()));

			float ModifiedBrowningRate =  BrowningRate;

			float MyPanBrowning = ModifiedBrowningRate * DeltaTime;
			steak->SetBrowningLevel(steak->GetBrowningLevel()+ModifiedBrowningRate * DeltaTime);



			UStaticMeshComponent* meshI = Actors[i]->FindComponentByClass<UStaticMeshComponent>();
			//     UE_LOG(LogTemp, Display, TEXT("OverLapping %s"), *(meshI->GetName()));
			//UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(meshI->GetMaterial(0), Actors[i]);
			UMaterialInstanceDynamic* material;
			material=meshI->CreateAndSetMaterialInstanceDynamicFromMaterial(0, (meshI->GetMaterial(0)));
			// UMaterialInstanceDynamic* MI = UMaterialInstanceDynamic::Create(Actors[i]->FindComponentByClass<UMeshComponent>()->GetMaterial(0),this);
			// MI->SetScalarParameterValue(FName(TEXT("Noise Range Start")), 5);
			// material->SetVectorParameterValue(FName(TEXT("LightColor")),FLinearColor(0.0,0.0,0.0,1.0);

			// Calculated Noise Starter, Noise Ender per tick interval
			float CalculationStartPerTickInterval = MyPanBrowning ;
			float CalculationEndPerTickInterval = MyPanBrowning ;
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

	}
}



