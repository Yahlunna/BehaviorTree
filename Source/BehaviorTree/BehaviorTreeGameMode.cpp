// Copyright Epic Games, Inc. All Rights Reserved.

#include "BehaviorTreeGameMode.h"
#include "BehaviorTreePlayerController.h"
#include "BehaviorTreeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABehaviorTreeGameMode::ABehaviorTreeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABehaviorTreePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}