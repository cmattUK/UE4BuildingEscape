// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYBUILDINGESCAPE_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UInteractWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateInteract(int32 Value);

	void ResetInteract();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBox* TxtInteract;
	
};
