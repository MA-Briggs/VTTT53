// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VTTButtonWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBUIOnClickedSignature, class UVTTButtonWidget*, Button);

UCLASS()
class VTT53_API UVTTButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Bind a function with the signature "void OnClicked(UBUIUWButton* Button);
	FBUIOnClickedSignature OnClickedDelegate;

protected:
	virtual void NativeConstruct() override;


public:
	// In the Blueprint subclass, make sure you create aButton called "MainButton"
	UPROPERTY(meta = (BindWidget))
	class UButton* MainButton;

	UFUNCTION()
	void OnButtonClicked();

	
};
