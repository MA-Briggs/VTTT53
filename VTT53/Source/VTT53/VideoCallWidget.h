// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "RemoteScreenWidget.h"
#include <Components/WidgetComponent.h>
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilitiesClasses.h"
#include "JsonObjectConverter.h"
#include <iostream>
#include "AgoraPluginInterface.h"

#include "Engine/TimerHandle.h"

#include "VideoCallWidget.generated.h"

/**
 * 
 */
USTRUCT()
struct FTokenResponse {
	GENERATED_BODY()

	UPROPERTY() FString key;
};

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
	FString _token;


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
	
	UFUNCTION(BlueprintCallable)
	void MuteVideo();
	UFUNCTION(BlueprintCallable)
	void UnMuteVideo();

	UFUNCTION(BlueprintCallable)
	void MuteAudio();
	UFUNCTION(BlueprintCallable)
	void UnMuteAudio();

	agora::rtc::ue::AgoraUERtcEngine* RtcEngineProxy;
	
	// Callback triggered when the local user leaves the channel
	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;
	
	// Callback triggered when the local user successfully joins the channel
	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;

	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;


	void onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason) override;

	void onTokenPrivilegeWillExpire( const char* token) override;


	// Create and initialize IRtcEngine
	void SetupSDKEngine();

	void RequestToken();
	void CallbackForRequestToken(FString NewToken);

protected:
	
	// Clean up all session-related resources
	void NativeDestruct() override;

	agora::rtc::CONNECTION_STATE_TYPE ConnectionState = agora::rtc::CONNECTION_STATE_TYPE::CONNECTION_STATE_DISCONNECTED;
	
	FTimerHandle TimerHandler;

	bool tokenFound = false;
};
