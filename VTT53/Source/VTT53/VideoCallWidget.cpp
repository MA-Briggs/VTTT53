// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoCallWidget.h"

void UVideoCallWidget::onTokenPrivilegeWillExpire(const char* token)
{
    //GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
    //GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UVideoCallWidget::RequestToken, 10.0f, true, 0.f);
    RequestToken();
}

void UVideoCallWidget::SetupSDKEngine()
{
    if (IconImage != nullptr) {
        agora::rtc::RtcEngineContext RtcEngineContext;
        // Set App ID
        RtcEngineContext.appId = TCHAR_TO_ANSI(*_appID);
        // Set event handler
        RtcEngineContext.eventHandler = this;
        // Create and initialize RtcEngineProxy
        RtcEngineProxy = agora::rtc::ue::AgoraUERtcEngine::Get();
        RtcEngineProxy->initialize(RtcEngineContext);
    }
}

void UVideoCallWidget::RequestToken()
{

    // Create Json Data
    /*FString ServerData;

    TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&ServerData);
    JsonWriter->WriteObjectStart();

    JsonWriter->WriteValue(TEXT("uid"), 0);
    JsonWriter->WriteValue(TEXT("ChannelName"), "Channel1");
    JsonWriter->WriteValue(TEXT("role"), 0);

    JsonWriter->WriteObjectEnd();
    JsonWriter->Close();*/


    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> request = FHttpModule::Get().CreateRequest();

    request->SetHeader("Content-Type", "application/json; charset=UTF-8");
    request->SetURL(FString("http://56.228.28.75:8080/rtcToken?channelName=Channel1"));
    request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr request, FHttpResponsePtr response, bool success) {
        //if (!success || !response.IsValid()) return false;
        
        FTokenResponse tokenResponse;
        FString JsonString = response->GetContentAsString();
        FJsonObjectConverter::JsonObjectStringToUStruct<FTokenResponse>(JsonString, &tokenResponse);
       
        CallbackForRequestToken(tokenResponse.key);

        });
    request->ProcessRequest();


}

void UVideoCallWidget::CallbackForRequestToken(FString NewToken)
{

    if (!NewToken.IsEmpty()) {
        _token = NewToken;
    }


    if (ConnectionState != agora::rtc::CONNECTION_STATE_DISCONNECTED && ConnectionState != agora::rtc::CONNECTION_STATE_FAILED)
    {
        RtcEngineProxy->renewToken(TCHAR_TO_UTF8(*_token));
    }
    tokenFound = true;
}


void UVideoCallWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (IconImage) {
        IconImage->SetDesiredSizeOverride(FVector2D(128.f, 96.f));
    }

    SetupSDKEngine();
    //RequestToken();
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

void UVideoCallWidget::Join(int IN_UID)
{
    //GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
    //GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UVideoCallWidget::RequestToken, 10.0f, true, 0.f);
    RequestToken();
    while (!tokenFound) {};

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
    RtcEngineProxy->joinChannel(TCHAR_TO_UTF8(*_token), TCHAR_TO_ANSI(_channelName), IN_UID, options);

    tokenFound = false;
}

void UVideoCallWidget::Leave()
{
    RtcEngineProxy->leaveChannel();
}

void UVideoCallWidget::MuteVideo()
{
    RtcEngineProxy->muteLocalVideoStream(true);
}

void UVideoCallWidget::UnMuteVideo()
{
    RtcEngineProxy->muteLocalVideoStream(false);

}

void UVideoCallWidget::MuteAudio()
{
    RtcEngineProxy->muteLocalAudioStream(true);
}

void UVideoCallWidget::UnMuteAudio()
{
    RtcEngineProxy->muteLocalAudioStream(false);

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
    for (auto& Screen : CPP_Screens) {
        if (uid == Cast<URemoteScreenWidget>(Screen->GetWidget())->UID) {
            agora::rtc::VideoCanvas videoCanvas;
            videoCanvas.view = Cast<URemoteScreenWidget>(Screen->GetWidget())->IconImage;
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
    for (auto& Screen : CPP_Screens) {
        if (uid == Cast<URemoteScreenWidget>(Screen->GetWidget())->UID) {
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

void UVideoCallWidget::onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
{
    ConnectionState = state;
}

