// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "TimerManager.h"
#include "InteractInterface.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYBUILDINGESCAPE_API UGrabber : public UActorComponent, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// add public interct function
	virtual void InteractPure(bool RotatableActor) override;

private:
	// Declare member of UPhysicsHandle component then initialize to nullptr to avoid crashes
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputCom = nullptr;
	FRotator StatueRotation;
	AActor* ActorThatsHit = nullptr;
	AActor* ActorInRange = nullptr;
	FTimerHandle  TimerHandle;


	void InteractWithObject();
	void DetectInteract();
	void Grab();
	void ReleaseObject();
	void FindPhysicsHandle();
	void SetupInputComponent();
	void RotateObject(float DeltaTime, AActor* ThisActor);

	float Reach = 150.f;
	float HoldDistance = 120.f;
	float GetDTime = 0.f;
	float CurrentYaw = 0.f;
	float StartingRotation = 0.f;
	float RotationAngle = 45.f;
	float EndRotation = 0.f;
	bool ActionClear = true;
	bool RotatableActorFound = false;
	bool ObjectNeedsRotating = false;
	float RotationSpeed = 30.f;

	FHitResult GetFirstPhysicsBodyInReach() const;
	FHitResult GetFirstActor() const;
	FVector GetPlayerReach() const;
	FVector GetPlayerHold() const;
	FVector GetPlayerWorldPos() const;
	
};