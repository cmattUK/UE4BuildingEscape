// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "StatueTurning.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYBUILDINGESCAPE_API UStatueTurning : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatueTurning();
	void FindAudioComp();
	void ResetStartPos();
	void GetCurrentPos();
	void PlaySound();

	float StatuePos;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FTimerManager RotateTimer;
	FTimerHandle TimerHandle;

	UPROPERTY()
	UAudioComponent* ThisAudioComponent = nullptr;
	bool SoundPlayed = false;
	bool StatueTriggered = false;
	float StatueStartPos;
	float CurrentTime = 0.f;
};
