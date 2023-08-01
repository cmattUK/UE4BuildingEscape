// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggereffect.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/TriggerVolume.h"


// Sets default values for this component's properties
UTriggereffect::UTriggereffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggereffect::BeginPlay()
{
	Super::BeginPlay();

	GetParticleSfxComp();

	// ...
	
}


// Called every frame
void UTriggereffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DetectTrigger();
	// ...
}

// Called when the game starts
void UTriggereffect::GetParticleSfxComp()
{
	ParticleSfxComp = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!ParticleSfxComp) {
		UE_LOG(LogTemp, Warning, TEXT("No audio component on: %s"), *GetOwner()->GetName());
	}
}
// Called every frame
void UTriggereffect::DetectTrigger()
{
	TArray<AActor*>OverlappingActors;
	if (FirePlate) {
		FirePlate->GetOverlappingActors(OUT OverlappingActors);

		for (int32 Index = 0; Index < OverlappingActors.Num(); Index++)
		{
			if (OverlappingActors[Index]->GetName() == "PlayerCharacter_C_0") {
				
				if (ParticleTriggered == false) {
					ParticleTriggeredTime = GetWorld()->GetTimeSeconds();
					PlayerActivatedTrigger = true;
				}
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Trigger volume attached to %"), *GetOwner()->GetName());
	}

	if (PlayerActivatedTrigger == true)
	{
		ActivateParticle();
	}
	// ...
}

// Called when the game starts
void UTriggereffect::ActivateParticle()
{
	bool SoundPlayed = false;
	if (ParticleSfxComp->IsPlaying())
	{
		return;
	}
	else
	{
		float DelayTime = 5.f;
		if ((ParticleTriggeredTime + DelayTime) >= GetWorld()->GetTimeSeconds()) {
			if (SoundPlayed == false)
			{
				ParticleSfxComp->Play();
				SoundPlayed = true;
				GetOwner()->GetRootComponent()->SetVisibility(true, false);
			}
		}
	}
	PlayerActivatedTrigger = false;
	ParticleTriggered = true;
	

}



