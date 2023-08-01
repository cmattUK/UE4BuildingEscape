// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "unlockPad.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYBUILDINGESCAPE_API UunlockPad : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UunlockPad();
	void DetectStatue();
	void FindAudioComp();
	void OpenChest(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	AActor* TriggerStatue = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* TriggerStatue2 = nullptr;

	//Set up a trigger volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerPlate = nullptr;

	//Set up a trigger volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerPlate2 = nullptr;

	UPROPERTY()
	UAudioComponent* ChestOpenSfxComp = nullptr;

	float addRotation = -90.f;
	float ChestOpenSpeed = 20.f;
	float StartingRoll = 0.f;
	float InitialRoll = 0.f;

	bool Unlocked = false;
	bool Trigger1 = false;
	bool Trigger2 = false;

	FRotator EndRotation;
};
