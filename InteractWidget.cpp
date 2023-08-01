// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"

UInteractWidget::UInteractWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInteractWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UInteractWidget::UpdateInteract(int32 Value)
{
	if (TxtInteract && Value > 1) 
	{
		if (TxtInteract->SetVisibility(ESlateVisibility::Hidden))
		{
			TxtInteract->SetVisibility(ESlateVisibility::Visible);
		}
		// generate output like 2X combo
		TxtInteract->SetText(FText::FromString(FString::FromInt(value) + "X Intercat"));
	}
}

void UInteractWidget::ResetInteract()
{
	if (Txtinteract) {
		TxtInteract->SetVisibility(ESlateVisibility::Hidden);
	}

}
