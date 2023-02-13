// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBounceGameMode.h"
#include "ProjectBounceCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectBounceGameMode::AProjectBounceGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
