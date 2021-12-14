// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoidsGameMode.h"
#include "BoidsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABoidsGameMode::ABoidsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
