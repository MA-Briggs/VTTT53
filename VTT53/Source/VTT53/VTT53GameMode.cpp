// Copyright Epic Games, Inc. All Rights Reserved.

#include "VTT53GameMode.h"
#include "VTT53Character.h"
#include "UObject/ConstructorHelpers.h"

AVTT53GameMode::AVTT53GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
