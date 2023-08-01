// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "StatueTurning.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	FindAudioComp();

	if (!TriggerStatR)
	{
		UE_LOG(LogTemp, Error, TEXT("No Right Statue"));
	}

	if (!TriggerStatL)
	{
		UE_LOG(LogTemp, Error, TEXT("No Left Statue"));
	}
}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerStatR && TriggerStatL) {
		if (BothDoors == true) {

			if ((TriggerStatR->GetActorRotation().Yaw == RotationStatR) && (TriggerStatL->GetActorRotation().Yaw == RotationStatL))
			{
				OpenDoor(DeltaTime);
			}
		}
		else if (BothDoors == false)
		{
			if (TriggerStatL->GetActorRotation().Yaw == RotationStatL)
			{

				OpenDoor(DeltaTime);
			}
		}
	}	
}

void UDoorOpen::OpenDoor(float DeltaTime)
{

	CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);

	FRotator OpenDoor = GetOwner()->GetActorRotation();

	OpenDoor.Yaw = CurrentYaw;

	GetOwner()->SetActorRotation(OpenDoor);


	if (OpenDoor.Yaw < OpenAngle) {
		if (DoorOpenSfxComp->IsPlaying()) {
			return;
		}
		else
		{
			if (SoundPlayed == false) {
				DoorOpenSfxComp->Play();
				SoundPlayed = true;
			}
		}

	}
}

void UDoorOpen::FindAudioComp()
{
	DoorOpenSfxComp = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!DoorOpenSfxComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component!"), *GetOwner()->GetName());
	}

}


