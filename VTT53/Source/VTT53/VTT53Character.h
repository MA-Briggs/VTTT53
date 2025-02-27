// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#if PLATFORM_ANDROID
#include "AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h"
#endif
#include "AgoraPluginInterface.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include <Components/WidgetComponent.h>
#include "VideoCallWidget.h"
#include "RemoteScreenWidget.h"
#include "VTT53PlayerController.h"

#include "VTT53Character.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AVTT53Character : public ACharacter, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
public:

	// Fill in your App ID
	FString _appID = "4ee00587a6914d4ab6fde16ee511dff8";
	// Fill in your channel name
	const TCHAR* _channelName = _T("Channel1");
	// Fill in Token
	const TCHAR* _token = _T("007eJxTYKgO8/isL2dV5W77ynuNwrXU+GM2C2dYsjF/e/9rxrH9rbcVGExSUw0MTC3ME80sDU1STBKTzNJSUg3NUlNNDQ1T0tIs4s4fSG8IZGQw/biUhZEBAkF8DgbnjMS8vNQcQwYGAPbtIio=");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int UID = 0;

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


public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly)
	UWidgetComponent* WidgetSelf;	

	UPROPERTY(BlueprintReadWrite)
	UImage* LocalCanvas = nullptr;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
public:
	//AVTT53Character(const class FPostConstructInitializeProperties& PCIP);
	AVTT53Character();

protected:
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TArray<UWidgetComponent*> CPP_Screens;

	UFUNCTION(BlueprintCallable)
	void SpawnScreen(int IN_WID);

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UFUNCTION(Client, Reliable)
	void SetWidgetLocal();

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> pWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> pWidgetClass2;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

};

