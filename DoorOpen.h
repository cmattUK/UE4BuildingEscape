// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYBUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();
	void OpenDoor(float DeltaTime);
	void FindAudioComp();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 
	UPROPERTY(EditAnywhere)
	AActor* TriggerStatL = nullptr;
	UPROPERTY(EditAnywhere)
	AActor* TriggerStatR = nullptr;

	float RotationStatR = -95.000061f;
	float RotationStatL = 90.000053f;
	
	UPROPERTY(EditAnywhere)
	bool BothDoors = false;
	bool SoundPlayed = false;

	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;

	UPROPERTY()
		UAudioComponent* DoorOpenSfxComp = nullptr;

	UPROPERTY(EditAnywhere)
		float OpenAngle = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorClosingSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.f;
};
