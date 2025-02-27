// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "VideoCallWidget.generated.h"

/**
 * 
 */
UCLASS()
class VTT53_API UVideoCallWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Initialize the custom Widget
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> IconImage;
};
