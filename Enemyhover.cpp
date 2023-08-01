// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemyhover.h"
#include "GameFramework/Actor.h"
#define OUT

// Sets default values for this component's properties
UEnemyhover::UEnemyhover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyhover::BeginPlay()
{
	Super::BeginPlay();
	InitialPos = GetOwner()->GetActorLocation().Z;
	CurrentPos = InitialPos;


	// ...
	
}


// Called every frame
void UEnemyhover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	EnemyHovering(DeltaTime);
	// ...
}

void UEnemyhover::EnemyHovering(float DeltaTime) 
{


	PositionNow = GetOwner()->GetActorLocation();

	if (PositionNow.Z >= HoverMaxMin) {
		//UE_LOG(LogTemp, Warning, TEXT("MaxHover: %f"), MaxHover);
		MaxHover = PositionNow.Z - HoverMaxMin;
		//UE_LOG(LogTemp, Warning, TEXT("MaxHover after peak: %f"), MaxHover);
	}
	else if (PositionNow.Z <= InitialPos) {
		MaxHover = PositionNow.Z + HoverMaxMin;
	}
	//CurrentPos = FMath::FInterpConstantTo(CurrentPos, MaxHover, DeltaTime, HoverSpeed);
	CurrentPos = FMath::InterpEaseInOut(CurrentPos, MaxHover, 1.f * DeltaTime, 150.f * DeltaTime);

	NewPosition = GetOwner()->GetActorLocation();

	NewPosition.Z = CurrentPos;

	GetOwner()->SetActorLocation(NewPosition);

	
}

