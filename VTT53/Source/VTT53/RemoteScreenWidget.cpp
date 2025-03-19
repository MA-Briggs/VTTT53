// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteScreenWidget.h"

void URemoteScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
    //SetupSDKEngine();
}

//void URemoteScreenWidget::onUserJoined(agora::rtc::uid_t uid, int elapsed)
//{
//    if (uid == UID) {
//        agora::rtc::VideoCanvas videoCanvas;
//        videoCanvas.view = IconImage;
//        videoCanvas.uid = uid;
//        videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;
//
//        agora::rtc::RtcConnection connection;
//        connection.channelId = TCHAR_TO_ANSI(_channelName);
//
//
//        ((agora::rtc::ue::AgoraUERtcEngine*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
//
//    }
//   
//}
//
//void URemoteScreenWidget::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
//{
//    if (uid == UID) {
//        agora::rtc::VideoCanvas videoCanvas;
//        videoCanvas.view = nullptr;
//        videoCanvas.uid = uid;
//        videoCanvas.sourceType = agora::rtc::VIDEO_SOURCE_TYPE::VIDEO_SOURCE_REMOTE;
//
//        agora::rtc::RtcConnection connection;
//        connection.channelId = TCHAR_TO_ANSI(_channelName);
//
//        ((agora::rtc::ue::AgoraUERtcEngine*)RtcEngineProxy)->setupRemoteVideoEx(videoCanvas, connection);
//    }
//}

//void URemoteScreenWidget::SetupSDKEngine(agora::rtc::ue::AgoraUERtcEngine* PassedInEngine)
//{
//   //
//    RtcEngineProxy = PassedInEngine;
//}
