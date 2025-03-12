// Copyright Epic Games, Inc. All Rights Reserved.

#include "VTT53Character.h"
#include "VTT53Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include <Net/UnrealNetwork.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AVTT53Character::AVTT53Character()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	//bReplicates = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	//static ConstructorHelpers::FClassFinder<URemoteScreenWidget> MyWidgetFinder2(TEXT("/Game/FirstPerson/Maps/TestWidget"));
	//if (MyWidgetFinder2.Succeeded())
	//{
	//	pWidgetClass2 = MyWidgetFinder2.Class;
	//}


}

//AVTT53Character::AVTT53Character()
//{
//}

void AVTT53Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		//WidgetSelf->SetOwnerPlayer(PlayerController->GetLocalPlayer());
	}


}

void AVTT53Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);
}

//////////////////////////////////////////////////////////////////////////// Input

void AVTT53Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVTT53Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVTT53Character::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AVTT53Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps); 

	DOREPLIFETIME(AVTT53Character, CPP_Screens);
	DOREPLIFETIME(AVTT53Character, UID);
}



void AVTT53Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AVTT53Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AVTT53Character::SpawnScreen(int IN_WID, int IN_UID)
{
	//UWidgetComponent* NewScreen = NewObject<UWidgetComponent>(this); //CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	//NewScreen->SetWidgetSpace(EWidgetSpace::World);
	//NewScreen->SetDrawAtDesiredSize(true);


	//URemoteScreenWidget* NewWidget = CreateWidget<URemoteScreenWidget>(GetWorld(), pWidgetClass2);
	//NewWidget->SetVisibility(ESlateVisibility::Visible);
	//NewWidget->WID = IN_WID;
	//NewWidget->UID = IN_UID;
	//NewScreen->SetWidget(NewWidget);
	//NewScreen->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	//NewScreen->RegisterComponent();
	//CPP_Screens.Add(NewScreen);
}

void AVTT53Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AVTT53Character::GetHasRifle()
{
	return bHasRifle;
}


void AVTT53Character::Join_Implementation()
{
	//
	//Cast<UVideoCallWidget>(WidgetSelf->GetWidget())->CPP_Screens = CPP_Screens;

	//Cast<UVideoCallWidget>(WidgetSelf->GetWidget())->Join(UID);
}

void AVTT53Character::Leave_Implementation()
{

	//Cast<UVideoCallWidget>(WidgetSelf->GetWidget())->Leave();

}

