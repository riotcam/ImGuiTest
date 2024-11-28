// Copyright Epic Games, Inc. All Rights Reserved.

#include "ImGuiTestGameMode.h"
#include "ImGuiTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AImGuiTestGameMode::AImGuiTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
