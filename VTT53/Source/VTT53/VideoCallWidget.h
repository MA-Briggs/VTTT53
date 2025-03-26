// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RemoteScreenWidget.h"
#include <Components/WidgetComponent.h>

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
	const TCHAR* _token = _T("007eJxTYBB7Wv+dW3nluZy5p1e1vtSzKhY4f+uU+2Y3dcHHs3t5ZGUVGExSUw0MTC3ME80sDU1STBKTzNJSUg3NUlNNDQ1T0tIsLKQfpzcEMjJMn1zBysgAgSA+B4NzRmJeXmqOIQMDAMPlIG8=");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int UID;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UWidgetComponent*> CPP_Screens;

	UFUNCTION(BlueprintCallable)
	void Join(int IN_UID);
	UFUNCTION(BlueprintCallable)
	void Leave();

	agora::rtc::ue::AgoraUERtcEngine* RtcEngineProxy;
	
	// Callback triggered when the local user leaves the channel
	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;
	
	// Callback triggered when the local user successfully joins the channel
	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;


	// Create and initialize IRtcEngine
	void SetupSDKEngine();

protected:
	
	// Clean up all session-related resources
	void NativeDestruct() override;


};
