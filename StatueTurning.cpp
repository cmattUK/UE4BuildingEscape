// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueTurning.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#define OUT

// Sets default values for this component's properties
UStatueTurning::UStatueTurning()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UStatueTurning::BeginPlay()
{
	Super::BeginPlay();
	FindAudioComp();
	StatueStartPos = GetOwner()->GetActorRotation().Yaw;
}

// Called every frame
void UStatueTurning::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)

{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT(" CurentPos: %f"),  GetOwner()->GetActorRotation().Yaw);
	float EndRotationTime = 10.f;
	//UE_LOG(LogTemp, Error, TEXT("statue location: %s"), *GetOwner()->GetVelocity().ToString());
	if (GetOwner()->GetActorRotation().Yaw != StatueStartPos) {
		if (StatueTriggered == false) {
			PlaySound();
		}
	}

	
}

void UStatueTurning::PlaySound()
{
	if (ThisAudioComponent->IsPlaying()) {
		return;
	}
	else
	{
		SoundPlayed = false;
		if (SoundPlayed == false)
		{
			SoundPlayed = true;
			StatueTriggered = true;
			ThisAudioComponent->Play();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UStatueTurning::ResetStartPos, 0.001f, false, 2.f);
			//UE_LOG(LogTemp, Warning, TEXT(" Time now: % f || Current: %f"), GetWorld()->GetTimeSeconds(), CurrentTime);

		}
	}
	
}
void UStatueTurning::ResetStartPos()
{	
	StatueStartPos = GetOwner()->GetActorRotation().Yaw;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	StatueTriggered = false;
}

void UStatueTurning::GetCurrentPos()
{
	StatueStartPos = GetOwner()->GetActorRotation().Yaw;
}

// Called every frame
void UStatueTurning::FindAudioComp()
{
	ThisAudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!ThisAudioComponent) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Audio comp on %s"), *GetOwner()->GetName());
	};
}


