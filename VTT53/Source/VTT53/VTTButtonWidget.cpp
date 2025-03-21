// Fill out your copyright notice in the Description page of Project Settings.


#include "VTTButtonWidget.h"
#include "Components/Button.h"

void UVTTButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClicked);
}

void UVTTButtonWidget::OnButtonClicked()
{
	OnClickedDelegate.Broadcast(this);
}
