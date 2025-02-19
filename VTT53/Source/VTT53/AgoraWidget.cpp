// Fill out your copyright notice in the Description page of Project Settings.


#include "AgoraWidget.h"

void UAgoraWidget::CheckAndroidPermission()
{
#if PLATFORM_ANDROID
    // Get the platform name
    FString pathfromName = UGameplayStatics::GetPlatformName();
    // Check if the platform is Android
    if (pathfromName == "Android")
    {
        // Array to store Android permissions
        TArray AndroidPermission;
        // Add required permissions
        AndroidPermission.Add(FString("android.permission.RECORD_AUDIO"));
        AndroidPermission.Add(FString("android.permission.READ_PHONE_STATE"));
        AndroidPermission.Add(FString("android.permission.WRITE_EXTERNAL_STORAGE"));
        // Request permissions
        UAndroidPermissionFunctionLibrary::AcquirePermissions(AndroidPermission);
    }
#endif
}


void UAgoraWidget::SetupSDKEngine()
{
    // Create RtcEngineContext
    agora::rtc::RtcEngineContext RtcEngineContext;
    // Set App ID
    RtcEngineContext.appId = TCHAR_TO_ANSI(*_appID);
    // Set event handler
    RtcEngineContext.eventHandler = this;
    // Create and initialize RtcEngineProxy
    RtcEngineProxy = agora::rtc::ue::AgoraUERtcEngine::Get();
    RtcEngineProxy->initialize(RtcEngineContext);
}
void UAgoraWidget::SetupUI()
{
    // Bind event handlers to UI buttons
    JoinButton->OnClicked.AddDynamic(this, &UAgoraWidget::Join);
    LeaveButton->OnClicked.AddDynamic(this, &UAgoraWidget::Leave);

}
void UAgoraWidget::Join()
{
    // Set channel media options
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
    RtcEngineProxy->joinChannel(TCHAR_TO_ANSI(_token), TCHAR_TO_ANSI(_channelName), 0 , options);
}
void UAgoraWidget::Leave()
{
    // Leave the channel
    RtcEngineProxy->leaveChannel();
}
void UAgoraWidget::NativeConstruct()
{
    Super::NativeConstruct();
#if PLATFORM_ANDROID
    // Check and request Android permissions
    CheckAndroidPermission();
#endif
    // Setup UI elements
    SetupUI();
    // Setup Agora SDK engine
    SetupSDKEngine();

    //Join();
}
void UAgoraWidget::NativeDestruct()
{
    //Leave();
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
void UAgoraWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed)
{
    // Callback when a remote user joins the channel

    agora::rtc::VideoCanvas videoCanvas;
    videoCanvas.view = RemoteCanvas;
    videoCanvas.uid = uid;
    videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

    agora::rtc::RtcConnection connection;
    connection.channelId = TCHAR_TO_ANSI(_channelName);

    
    ((agora::rtc::ue::AgoraUERtcEngine*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);

}
void UAgoraWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
{
    // Callback when a remote user leaves the channel
    agora::rtc::VideoCanvas videoCanvas;
    videoCanvas.view = nullptr;
    videoCanvas.uid = uid;
    videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;

    agora::rtc::RtcConnection connection;
    connection.channelId = TCHAR_TO_ANSI(_channelName);

    ((agora::rtc::ue::AgoraUERtcEngine*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);

}
void UAgoraWidget::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
{
    // Callback when the local user successfully joins the channel
    AsyncTask(ENamedThreads::GameThread, [=, this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("JoinChannelSuccess uid: %u"), uid);

        agora::rtc::VideoCanvas videoCanvas;
        videoCanvas.view = LocalCanvas;
        videoCanvas.uid = 0;
        videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
        RtcEngineProxy->setupLocalVideo(videoCanvas);
    });

    UID = uid;
}

void UAgoraWidget::onLeaveChannel(const agora::rtc::RtcStats& stats)
{
   /* AsyncTask(ENamedThreads::GameThread, [=, this]()
        {
            agora::rtc::VideoCanvas videoCanvas;
            videoCanvas.view = nullptr;
            videoCanvas.uid = 0;
            videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_CAMERA;
            RtcEngineProxy->setupLocalVideo(videoCanvas);
        });*/
}