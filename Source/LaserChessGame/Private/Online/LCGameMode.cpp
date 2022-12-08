// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Online/LCGameMode.h"
#include "Online/LCGameState.h"
#include "Online/LCGameSession.h"
#include "Player/LCCameraPawnController.h"

ALCGameMode::ALCGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = ALCCameraPawnController::StaticClass();
	GameSessionClass = ALCGameSession::StaticClass();
	GameStateClass = ALCGameState::StaticClass(); 
}
