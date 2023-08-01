// Fill out your copyright notice in the Description page of Project Settings.


#include "unlockPad.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"

// Sets default values for this component's properties
UunlockPad::UunlockPad()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UunlockPad::BeginPlay()
{
	Super::BeginPlay();
	FindAudioComp();


	if (!TriggerStatue) {
		UE_LOG(LogTemp, Error, TEXT("No TriggerStatue set on %s"), *GetOwner()->GetName());
	}
	if (!TriggerPlate) {
		UE_LOG(LogTemp, Error, TEXT("No TriggerPlate set on %s"), *GetOwner()->GetName());
	}
	if (!TriggerStatue2) {
		UE_LOG(LogTemp, Error, TEXT("No TriggerStatue set on %s"), *GetOwner()->GetName());
	}
	if (!TriggerPlate2) {
		UE_LOG(LogTemp, Error, TEXT("No TriggerPlate set on %s"), *GetOwner()->GetName());
	}
	InitialRoll = GetOwner()->GetActorRotation().Roll;
	StartingRoll = InitialRoll;
}


// Called every frame
void UunlockPad::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DetectStatue();
	if ((Trigger1 == true) && (Trigger2 == true))
	{
		OpenChest(DeltaTime);
	}
}

void UunlockPad::DetectStatue() 
{
	if (TriggerStatue && TriggerStatue2)
	{
		TArray<AActor*>OverlappingActors;
		TriggerPlate->GetOverlappingActors(OUT OverlappingActors);

		for (int32 Index = 0; Index < OverlappingActors.Num(); Index++)
		{
			if (OverlappingActors[Index] == TriggerStatue)
			{
				Trigger1 = true;
			}
		}

		TArray<AActor*>OverlappingActors2;
		TriggerPlate2->GetOverlappingActors(OUT OverlappingActors2);

		for (int32 Index = 0; Index < OverlappingActors2.Num(); Index++)
		{
			if (OverlappingActors2[Index] == TriggerStatue2)
			{
				Trigger2 = true;
			}
		}
	}
	
}

void UunlockPad::OpenChest(float DeltaTime)
{
	if (GetOwner()->GetActorRotation().Roll == InitialRoll)
	{
		bool SoundPlayed = false;
		if (ChestOpenSfxComp->IsPlaying()) {
			return;
		}
		else
		{
			if (SoundPlayed == false) {
				ChestOpenSfxComp->Play();
				SoundPlayed = true;
			}
		}
	}
	
	// Lerp the Yaw between CurrentYaw and OpenAngle
	//!!!interpolation with easing!!!
	StartingRoll = FMath::FInterpConstantTo(StartingRoll, addRotation, DeltaTime, ChestOpenSpeed);
	// Create an FRotator called Open door with current rotation
	FRotator OpenChest = GetOwner()->GetActorRotation();

	//!!!Constant interpolation!!!
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, -OpenAngle, DeltaTime, 90);

	OpenChest.Roll = StartingRoll;
	//Fire the Lerp on the actor
	GetOwner()->SetActorRotation(OpenChest);
	
}

void UunlockPad::FindAudioComp()
{
	ChestOpenSfxComp = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!ChestOpenSfxComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component!"), *GetOwner()->GetName());
	}

}


