// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	FindAudioComp();
	// ...
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	


	// Lerp the Yaw between CurrentYaw and OpenAngle
	//!!!interpolation with easing!!!
	CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	// Create an FRotator called Open door with current rotation
	FRotator OpenDoor = GetOwner()->GetActorRotation();

	//!!!Constant interpolation!!!
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, -OpenAngle, DeltaTime, 90);

	OpenDoor.Yaw = CurrentYaw;
	//Fire the Lerp on the actor
	GetOwner()->SetActorRotation(OpenDoor);

	//UE_LOG(LogTemp, Warning, TEXT("Open Door! %f"), OpenDoor.Yaw);

	/*if (OpenDoor.Yaw < OpenAngle)
	{
		bool SoundPlayed = false;
		if (AudioComponent->IsPlaying()) {
			return;
		}
		else
		{
			if (SoundPlayed == false) {
				AudioComponent->Play();
				SoundPlayed == true;
			}
		}
	}*/

	if (OpenDoor.Yaw < OpenAngle) {
		bool SoundPlayed = false;
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

void UOpenDoor::FindAudioComp()
{
	DoorOpenSfxComp = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!DoorOpenSfxComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component!"), *GetOwner()->GetName());
	}

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	OpenDoor(DeltaTime);

	// ...
}

