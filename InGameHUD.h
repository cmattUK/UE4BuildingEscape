// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "InteractWidget.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYBUILDINGESCAPE_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	AInGameHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void UpdateInteract(int32 Value);
		void ResetInteract();

	UPROPERTY(EditDefaultOnly, Category = "widgets")
		TSubclassOf<UUserWidget> InteractWidgetClass;

private:
	UInteractWidget* InteractWidget;
	
};
