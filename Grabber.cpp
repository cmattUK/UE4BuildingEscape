// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"

//define something
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DetectInteract();

	GetDTime = GetWorld()->GetDeltaSeconds();
	if (ObjectNeedsRotating == true)
	{
		RotateObject(DeltaTime, ActorThatsHit);
	}
	//!!!!!!Protect from nullptr crash if theres no physicshandle!!!!!
	if (!PhysicsHandle) { return; }
	// 	if physics handle is attached and has a grabbed component
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}

}

FVector UGrabber::GetPlayerReach() const
{

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	return PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;

}

FVector UGrabber::GetPlayerHold() const
{

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	return PlayerViewpointLocation + PlayerViewpointRotation.Vector() * HoldDistance;

}

FVector UGrabber::GetPlayerWorldPos() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	return PlayerViewpointLocation;
}

// check for input component
void UGrabber::SetupInputComponent()
{
	//Returns first component of the specified class
	//!!!don't have to protect because any component that is on an actor is not a nullptr
	InputCom = GetOwner()->FindComponentByClass<UInputComponent>();
	//protect from crash
	if (InputCom)
	{
		//input component is found
		//UE_LOG(LogTemp, Warning, TEXT("Input component attached to: %s "), *GetOwner()->GetName());

		//bind action (set-up in preferences>input) to input component
		InputCom->BindAction("InteractWithObject", IE_Pressed, this, &UGrabber::InteractWithObject);
		InputCom->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputCom->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseObject);
		/*BindCation params =
			1) The name of the set up action
			2) The type of action that triggers it
			3) The object
			4) Address (&) to a function
		*/
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Input component attached to: %s"), *GetOwner()->GetName());
	}
}

// check for physics handle component
void UGrabber::FindPhysicsHandle()
{
	//Returns first component of the specified class
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//!!!!!!!protect from null pointer crash!!!!!
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics handle attached to: %s"), *GetOwner()->GetName());
	}
}

//Grab object
void UGrabber::DetectInteract()
{
	FHitResult HitP = GetFirstPhysicsBodyInReach();
	AActor* ActorInRangePhysics = HitP.GetActor();
	AActor* ActorHitEither = nullptr;

	FHitResult HitR = GetFirstActor();
	ActorInRange = HitR.GetActor();

	if (ActorInRange) {
		ActorHitEither = ActorInRange;
	}
	else if (ActorInRangePhysics)
	{
		ActorHitEither = ActorInRangePhysics;
	}
	
	if (ActorHitEither) {
		if (ActorHitEither->GetRootComponent()->ComponentHasTag("Int")) {
			if (ActorHitEither->GetRootComponent()->ComponentHasTag("Grab"))
			{
				RotatableActorFound = false;
			}
			else if (ActorHitEither->GetRootComponent()->ComponentHasTag("Rotate"))
			{
				RotatableActorFound = true;
			}
			InteractPure(RotatableActorFound);
		}
	}
}

//Grab object
void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	//If we hit something, then attach physics handle
	if (ActorHit)
	{
		if (ActorHit->GetRootComponent()->ComponentHasTag("Int"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Int!!!"));
		}
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			GetPlayerHold()
		);

	}
}

//release object
void UGrabber::ReleaseObject()
{
	//!!!!!!Protect from nullptr crash if theres no physicshandle!!!!!
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Released"));
	//TODO remove/release physics handle
}

//Interact with object
void UGrabber::InteractWithObject()
{
	if (ActionClear == true) {
	FHitResult HitResult = GetFirstActor();
	ActorThatsHit = HitResult.GetActor();
		if (ActorThatsHit)
		{
			if ((ActorThatsHit->GetName() == "TriggerStatueLarge") || (ActorThatsHit->GetName() == "TriggerStatueLarge_2"))
			{
				
				CurrentYaw = ActorThatsHit->GetActorRotation().Yaw;
				EndRotation = CurrentYaw + RotationAngle;
				ObjectNeedsRotating = true;
				ActionClear = false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("%S NOT interacted with"), *ActorThatsHit->GetName());
			}
		}
	}
}

//Interact with object
void UGrabber::RotateObject(float DeltaTime, AActor* ThisActor)
{
		CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, EndRotation, DeltaTime, RotationSpeed);
		FRotator StatRotation = ThisActor->GetActorRotation();
		StatRotation.Yaw = CurrentYaw;
		ThisActor->SetActorRelativeRotation(StatRotation, false, 0, ETeleportType::None);
		if (StatRotation.Yaw == EndRotation) {
			ObjectNeedsRotating = false;
			ActionClear = true;
		}
}

FHitResult UGrabber::GetFirstActor() const
{
	FHitResult hit;

	//TRACE PARAMS: Param 1: tag name (we aren't looking for tags here), Param 2: Are we using complex collision?, Param3: what do we need to ignore?
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT hit,
		GetPlayerWorldPos(),
		GetPlayerReach(),
		//set collision channel for object type
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParams
	);
		
	AActor* ActorHit = hit.GetActor();

	if (ActorHit) {
		//UE_LOG(LogTemp, Error, TEXT("Actor hit: %s"), *ActorHit->GetName());
	}
	return hit;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// 		//Draw a line form the player
	// 		//line endpoint
	// 		FVector LineTraceDirection = PlayerViewpointRotation.Vector();
	// 		FVector LineTraceEnd = PlayerViewpointLocation + LineTraceDirection * Reach;
	// 	
	// 		//draw debug line
	// 		DrawDebugLine
	// 		(
	// 			GetWorld(),
	// 			PlayerViewpointLocation, 
	// 			LineTraceEnd, 
	// 			FColor(0, 255, 0), 
	// 			false, 
	// 			0.f, 
	// 			0, 
	// 			3.f
	// 		);

	FHitResult hit;

	//TRACE PARAMS: Param 1: tag name (we aren't looking for tags here), Param 2: Are we using complex collision?, Param3: what do we need to ignore?
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT hit,
		GetPlayerWorldPos(),
		GetPlayerReach(),
		//set collision channel for object type
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = hit.GetActor();

	if (ActorHit) {
		//UE_LOG(LogTemp, Error, TEXT("Actor hit: %s"), *ActorHit->GetName());
	}
	return hit;
}

void UGrabber::InteractPure(bool RotatableActor)
{
	if (RotatableActor == true)
	{
		UE_LOG(LogTemp, Error, TEXT("Rotatable"));
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Non rotatble"));
	}
	
}

