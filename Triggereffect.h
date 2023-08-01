// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Triggereffect.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYBUILDINGESCAPE_API UTriggereffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggereffect();
	void ActivateParticle();
	void DetectTrigger();
	void GetParticleSfxComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Set up a trigger volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* FirePlate = nullptr;

	UPROPERTY()
	UParticleSystem* ParticleToTrigger = nullptr;

	UPROPERTY()
	UAudioComponent* ParticleSfxComp = nullptr;

	bool PlayerActivatedTrigger = false;
	bool ParticleTriggered = false;
	float ParticleTriggeredTime = 0.f;
};
