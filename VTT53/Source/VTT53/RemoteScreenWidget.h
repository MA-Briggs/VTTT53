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
	int WID;
	UPROPERTY(BlueprintReadWrite)
	int UID;

	// Fill in your App ID
	FString _appID = "4ee00587a6914d4ab6fde16ee511dff8";
	// Fill in your channel name
	const TCHAR* _channelName = _T("Channel1");
	// Fill in Token
	const TCHAR* _token = _T("007eJxTYKi8t2xPt3nhrR9lDCX3Filu1Df5en+v1acTDCu2T2f1mealwGCSmmpgYGphnmhmaWiSYpKYZJaWkmpolppqamiYkpZmcdz3RHpDICNDHNtdVkYGCATxORicMxLz8lJzDBkYAGy+IpQ=");

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IconImage;

	agora::rtc::ue::AgoraUERtcEngine* RtcEngineProxy;

protected:

	virtual void NativeConstruct() override;

	//void onUserJoined(agora::rtc::uid_t uid, int elapsed);
	// Callback triggered when a remote broadcaster leaves the channel
	//void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason);

public:
	//void SetupSDKEngine(agora::rtc::ue::AgoraUERtcEngine* PassedInEngine);
	
};
