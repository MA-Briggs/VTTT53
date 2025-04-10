// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AgoraPluginInterface.h"
#include "Components/Image.h"
#include "RemoteScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class VTT53_API URemoteScreenWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	int UID;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IconImage;


protected:

	virtual void NativeConstruct() override;

};
