// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "AgoraPluginInterface.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "AgoraWidget.generated.h"
UCLASS()
class VTT53_API UAgoraWidget : public UUserWidget, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
public:
	// Fill in your App ID
	FString _appID = "4ee00587a6914d4ab6fde16ee511dff8";
	// Fill in your channel name
	const TCHAR* _channelName = _T("Channel1");
	// Fill in Token
	const TCHAR* _token = _T("007eJxTYPijq8BZnFr3cFWNb/T6mbN8eldvuRi5TPyqlprgr9e7Pl9QYDBJTTUwMLUwTzSzNDRJMUlMMktLSTU0S001NTRMSUuz8H2xJr0hkJGhcasKAyMUgvgcDM4ZiXl5qTmGDAwAQgwilA==");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int UID = 0;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LocalCanvas = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* RemoteCanvas = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinButton = nullptr;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* LeaveButton = nullptr;

	UFUNCTION(BlueprintCallable)
	void Join();
	UFUNCTION(BlueprintCallable)
	void Leave();
	agora::rtc::ue::AgoraUERtcEngine* RtcEngineProxy;
	// Callback triggered when the local user leaves the channel
	void onLeaveChannel(const agora::rtc::RtcStats& stats) override;
	// Callback triggered when a remote broadcaster successfully joins the channel
	void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;
	// Callback triggered when a remote broadcaster leaves the channel
	void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;
	// Callback triggered when the local user successfully joins the channel
	void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
private:
	// Get Android permissions
	void CheckAndroidPermission();
    
	// Create and initialize IRtcEngine
	void SetupSDKEngine();
    
	// Set up UI elements
	void SetupUI();
protected:
	// Initialize the custom Widget
	void NativeConstruct() override;
    
	// Clean up all session-related resources
	void NativeDestruct() override;

	
};