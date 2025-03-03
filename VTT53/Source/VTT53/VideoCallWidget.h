// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "AgoraPluginInterface.h"

#include "VideoCallWidget.generated.h"

/**
 * 
 */
UCLASS()
class VTT53_API UVideoCallWidget : public UUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
protected:
	// Initialize the custom Widget
	virtual void NativeConstruct() override;
public:

	// Fill in your App ID
	FString _appID = "4ee00587a6914d4ab6fde16ee511dff8";
	// Fill in your channel name
	const TCHAR* _channelName = _T("Channel1");
	// Fill in Token
	const TCHAR* _token = _T("007eJxTYIht044/ufdNcOSqMNsj6q7vXBPSTh62FTnVu8LpkMHr55kKDCapqQYGphbmiWaWhiYpJolJZmkpqYZmqammhoYpaWkWpu+PpjcEMjK0S71iZGSAQBCfg8E5IzEvLzXHkIEBABc7Iho=");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int UID = 0;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	UFUNCTION(BlueprintCallable)
	void Join();
	UFUNCTION(BlueprintCallable)
	void Leave();
	agora::rtc::ue::AgoraUERtcEngine* RtcEngineProxy;
	// Callback triggered when the local user leaves the channel
	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

	
	// Callback triggered when the local user successfully joins the channel
	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
private:

	// Create and initialize IRtcEngine
	void SetupSDKEngine();

protected:
	
	// Clean up all session-related resources
	void NativeDestruct() override;


};
