// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enemyhover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYBUILDINGESCAPE_API UEnemyhover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyhover();
	void EnemyHovering(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	float InitialPos;
	float CurrentPos;
	UPROPERTY(EditAnywhere)
	float HoverMaxMin = 30.f;
	UPROPERTY(EditAnywhere)
	float HoverSpeed = 6.f;
	float MaxHover;
	UPROPERTY()
	FVector PositionNow;
	UPROPERTY()
	FVector NewPosition;


};
