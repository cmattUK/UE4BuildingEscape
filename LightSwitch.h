// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "RenderCore.h"
#include "TimerManager.h"
#include "LightSwitch.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYBUILDINGESCAPE_API ULightSwitch : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightSwitch();
	void SwitchOnLight(float DeltaTime);
	void GetAudioComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//Set up a trigger volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* LightPlate = nullptr;

	UPROPERTY()
	UAudioComponent* LightSfxComp = nullptr;

	FTimer PressTimer;

	float CurrentTime = 0.f;
	bool PlayerActivatedTrigger = false;
	bool LightTriggered = false;
	float LightSpeed;
	float TimeActivated;

	UPROPERTY(EditAnywhere)
	float LightDelay = 0.f;

	UPROPERTY(EditAnywhere)
	float InitialIntensity = 0.f;

	UPROPERTY(EditAnywhere)
	float FinalIntensity = 0.f;

	UPROPERTY(EditAnywhere)
	float LightIntensitySpeed = 0.f;


};
