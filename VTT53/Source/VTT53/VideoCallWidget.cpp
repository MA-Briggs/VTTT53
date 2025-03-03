// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoCallWidget.h"

void UVideoCallWidget::SetupSDKEngine()
{
    agora::rtc::RtcEngineContext RtcEngineContext;
    // Set App ID
    RtcEngineContext.appId = TCHAR_TO_ANSI(*_appID);
    // Set event handler
    RtcEngineContext.eventHandler = this;
    // Create and initialize RtcEngineProxy
    RtcEngineProxy = agora::rtc::ue::AgoraUERtcEngine::Get();
    RtcEngineProxy->initialize(RtcEngineContext);
}

void UVideoCallWidget::NativeConstruct()
{
	Super::NativeConstruct();
    if (IconImage) {
        IconImage->SetDesiredSizeOverride(FVector2D(128.f, 96.f));
    }

    SetupSDKEngine();
}

void UVideoCallWidget::NativeDestruct()
{
    Super::NativeDestruct();
    // Clean up resources
    if (RtcEngineProxy != nullptr)
    {
        RtcEngineProxy->unregisterEventHandler(this);
        RtcEngineProxy->Release();
        //delete RtcEngineProxy;
        RtcEngineProxy = nullptr;
    }
}

void UVideoCallWidget::Join()
{
    agora::rtc::ChannelMediaOptions options;
    RtcEngineProxy->enableVideo();

    // Automatically subscribe to all audio streams
    options.autoSubscribeAudio = true;

    options.autoSubscribeVideo = true;

    // Publish the audio collected by the microphone
    options.publishMicrophoneTrack = true;

    options.publishCameraTrack = true;

    // Set channel profile to live broadcasting
    options.channelProfile = agora::CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION;
    // Set user role to broadcaster
    options.clientRoleType = agora::rtc::CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER;
    // Join the channel
    RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(_token), TCHAR_TO_ANSI(_channelName), 0, options);
}

void UVideoCallWidget::Leave()
{
    RtcEngineProxy->leaveChannel();
}

void UVideoCallWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
    AsyncTask(ENamedThreads::GameThread, [=, this]()
        {
            agora::rtc::VideoCanvas videoCanvas;
            videoCanvas.view = nullptr;
            videoCanvas.uid = 0;
            videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
            RtcEngineProxy->setupLocalVideo(videoCanvas);
        });
}


void UVideoCallWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
    AsyncTask(ENamedThreads::GameThread, [=, this]()
        {
            UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess uid: %u"), uid);

            agora::rtc::VideoCanvas videoCanvas;
            videoCanvas.view = IconImage;
            videoCanvas.uid = 0;
            videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
            RtcEngineProxy->setupLocalVideo(videoCanvas);
        });

    UID = uid;
}
