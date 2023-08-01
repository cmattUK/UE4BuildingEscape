// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Components/LightComponent.h"
#include "Engine/PointLight.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"


#define OUT

// Sets default values for this component's properties
ULightSwitch::ULightSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void ULightSwitch::BeginPlay()
{
	Super::BeginPlay();
	// ...
	if (!LightPlate) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No LightPlate set on: %s"), *GetOwner()->GetName());
	}
	GetAudioComponent();

	
}

void ULightSwitch::GetAudioComponent()
{
	LightSfxComp = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!LightSfxComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component!"), *GetOwner()->GetName());
	}

}

void ULightSwitch::SwitchOnLight(float DeltaTime)
{
		PressTimer.Tick(DeltaTime);
		CurrentTime = PressTimer.GetCurrentTime();
		LightSpeed = FMath::FInterpTo(InitialIntensity, FinalIntensity, DeltaTime, LightIntensitySpeed);
		AActor* ThisLight = GetOwner();

		//UE_LOG(LogTemp, Warning, TEXT("%f"), GetCurrentTime);

			if (CurrentTime > LightDelay) {
				ThisLight->FindComponentByClass<ULightComponent>()->SetIntensity(LightSpeed);
				if (LightSfxComp)
				{
					bool SoundPlayed = false;
					if (LightSfxComp->IsPlaying())
					{
						return;
					}
					else
					{
						if (SoundPlayed == false)
						{
							//UE_LOG(LogTemp, Warning, TEXT("Playing Sound "));
							LightSfxComp->Play();
							SoundPlayed = true;
						}
					}
				}
				PlayerActivatedTrigger = false;
				LightTriggered = true;
			}
		
		
}

// Called every frame
void ULightSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TArray<AActor*>OverlappingActors;
	if (LightPlate) {
		LightPlate->GetOverlappingActors(OUT OverlappingActors);

		for (int32 Index = 0; Index < OverlappingActors.Num(); Index++)
		{
			if (OverlappingActors[Index]->GetName() == "PlayerCharacter_C_0") {
				if (LightTriggered == false) {
				//	UE_LOG(LogTemp, Warning, TEXT("Player on trigger"));
					PlayerActivatedTrigger = true;
				}
			}
		}
	}

	if (PlayerActivatedTrigger == true)
	{
		SwitchOnLight(DeltaTime);
	}
}

