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
class AVTT53Character : public ACharacter//, public agora::rtc::IRtcEngineEventHandler
{
	GENERATED_BODY()
public:
	// Fill in your App ID
	FString _appID = "4ee00587a6914d4ab6fde16ee511dff8";
	// Fill in your channel name
	const TCHAR* _channelName = _T("Channel1");
	// Fill in Token
	const TCHAR* _token = _T("007eJxTYKi8t2xPt3nhrR9lDCX3Filu1Df5en+v1acTDCu2T2f1mealwGCSmmpgYGphnmhmaWiSYpKYZJaWkmpolppqamiYkpZmcdz3RHpDICNDHNtdVkYGCATxORicMxLz8lJzDBkYAGy+IpQ=");


	UFUNCTION(BlueprintCallable, Client, Reliable)
	void Join();

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void Leave();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	int UID;

	
	//agora::rtc::ue::AgoraUERtcEngine* RtcEngineProxy;
	// Callback triggered when the local user leaves the channel
	//void onLeaveChannel(const agora::rtc::RtcStats& stats) override;


	// Callback triggered when the local user successfully joins the channel
	//void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly)
	UWidgetComponent* WidgetSelf;	
	
	UPROPERTY(VisibleDefaultsOnly)
	UVideoCallWidget* WidgetTest;	

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
	void SpawnScreen(int IN_WID, int IN_UID);

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UFUNCTION(BlueprintCallable, Client, Reliable)
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

