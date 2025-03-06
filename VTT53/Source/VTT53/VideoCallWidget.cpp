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
    if (RtcEngineProxy != nullptr && RtcEngineProxy->NativeRtcEnginePtr() != nullptr)
    {
        RtcEngineProxy->unregisterEventHandler(this);
        RtcEngineProxy->Release();
        //delete RtcEngineProxy;
        RtcEngineProxy = nullptr;
    }
}

void UVideoCallWidget::Join_Implementation(int IN_UID)
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
    RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(_token), TCHAR_TO_ANSI(_channelName), IN_UID, options);
}

void UVideoCallWidget::Leave_Implementation()
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
    if (this) {
        AsyncTask(ENamedThreads::GameThread, [=, this]()
            {
                UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess uid: %u"), uid);

                agora::rtc::VideoCanvas videoCanvas;
                videoCanvas.view = IconImage;
                videoCanvas.uid = 0;
                videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
                RtcEngineProxy->setupLocalVideo(videoCanvas);
            });
    }
    //UID = uid;
}

void UVideoCallWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
    for (int i = 0; i <= CPP_Screens.Num(); i++) {
        if (uid == Cast<URemoteScreenWidget>(CPP_Screens[i]->GetWidget())->UID) {
            agora::rtc::VideoCanvas videoCanvas;
            videoCanvas.view = Cast<URemoteScreenWidget>(CPP_Screens[i]->GetWidget())->IconImage;
            videoCanvas.uid = uid;
            videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

            agora::rtc::RtcConnection connection;
            connection.channelId = TCHAR_TO_ANSI(_channelName);


            ((agora::rtc::ue::AgoraUERtcEngine*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);

        }
    }
}

void UVideoCallWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
    for (int i = 0; i <= CPP_Screens.Num(); i++) {
        if (uid == Cast<URemoteScreenWidget>(CPP_Screens[i]->GetWidget())->UID){
            agora::rtc::VideoCanvas videoCanvas;
            videoCanvas.view = nullptr;
            videoCanvas.uid = uid;
            videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

            agora::rtc::RtcConnection connection;
            connection.channelId = TCHAR_TO_ANSI(_channelName);

            ((agora::rtc::ue::AgoraUERtcEngine*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
        }
    }
}

