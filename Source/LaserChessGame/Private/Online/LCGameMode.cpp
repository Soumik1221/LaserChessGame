// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Online/LCGameMode.h"
#include "Online/LCGameState.h"
#include "Online/LCGameSession.h"
#include "Player/LCCameraPawnController.h"
#include "Game/LaserChessGameTypes.h"

ALCGameMode::ALCGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = ALCCameraPawnController::StaticClass();
	GameSessionClass = ALCGameSession::StaticClass();
	GameStateClass = ALCGameState::StaticClass(); 
	
	BoardSetup = EBoardSetup::EBS_ACE;
	bIsAllPlayerJoined = false;
	bIsReadyToPlay = false;
	bIsGameInitialized = false;
	bIsGamePlaying = false;
	PlayerReadyCheckFrequency = 0.5f;
	MaxPlayerPendingReady = 500.0f;
}

void ALCGameMode::BeginPlay()
{
	Super::BeginPlay();
	LCGameStateRef = GetGameState<ALCGameState>();
	LCGameSessionRef = Cast<ALCGameSession>(GameSession);
	
	// TODO: This should pass from internal system during map load.
	bIsOfflineGame = (GetNetMode() == NM_Standalone);

	// Offline game 
	if(bIsOfflineGame)
	{
		InitGame(EBoardSetup::EBS_ACE);
		UE_LOG(LogLaserChess, Log, TEXT("Playing Offline Game"));
		FLaserChessAIInitParam InitParams;
		InitLaserChessAI(InitParams);
		bIsAllPlayerJoined = true;
	}
}

void ALCGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	if(bIsAllPlayerJoined)
	{
		ErrorMessage = TEXT("No Empty spot for new player.");
	}
	else
	{
		Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	}
}

void ALCGameMode::PostLogin(APlayerController* NewPlayer)
{
	// @TODO: Maybe Check if unique player controller This May be don't need to be checked.
	Super::PostLogin(NewPlayer);

	// Only accept player if player no game is running and have space for player.
	if(!bIsAllPlayerJoined && !bIsGamePlaying)
	{
		if(ALCCameraPawnController* Player = Cast<ALCCameraPawnController>(NewPlayer))
		{
			// Join the first player
			if (!Player0)
			{
				bIsPlayer0TeamA = (Player->GetPlayerChosenTeam() == EPawnTeam::EPT_TeamA);
				Player0 = Player;
				UE_LOG(LogLaserChess, Log, TEXT("Player0 Logged In: %s,"), *Player->GetName());
			}
			
			// Online game
			// Check if logged in player already not set as Player0 TODO: Check This check may be redundant
			if(!bIsOfflineGame && Player != Player0) 
			{
				Player1 = Player;
				UE_LOG(LogLaserChess, Log, TEXT("Player1 Logged In: %s"), *Player->GetName());
				bIsAllPlayerJoined = true;
				bIsReadyToPlay = false;
				HandleAllPlayerJoined();
				UE_LOG(LogLaserChess, Log, TEXT("Playing Online Game"));
			}
		}
	}
}

void ALCGameMode::Logout(AController* Exiting)
{
	const bool bIsPlayer0Exiting = (Player0 == Exiting);
	const bool bIsPlayer1Exiting = (Player1 == Exiting);

	if(bIsPlayer0Exiting && !bIsPlayer1Exiting)
	{
		Player0 = Player1; // Move player 0 to player 1
		InvalidateSecondPlayer();
	}
	if (!bIsPlayer0Exiting && bIsPlayer1Exiting)
	{
		InvalidateSecondPlayer();
	}
	
	Super::Logout(Exiting);
}

void ALCGameMode::InitGame(EBoardSetup InSetup)
{
	Player0->SetServerPawnTeam(bIsPlayer0TeamA ? EPawnTeam::EPT_TeamA : EPawnTeam::EPT_TeamB);
	
	if(!bIsOfflineGame)
		Player1->SetServerPawnTeam(bIsPlayer0TeamA ? EPawnTeam::EPT_TeamB : EPawnTeam::EPT_TeamA);

	if (LCGameStateRef)
	{
		UE_LOG(LogLaserChess, Log, TEXT("Laser Chess Game state valid"));
		BoardSetup = InSetup;
		LCGameStateRef->SpawnGameTilesServer();
		LCGameStateRef->SpawnGamePawnServer(BoardSetup);
	}

	UE_LOG(LogLaserChess, Log, TEXT("LaserChessGame Initialized, Player0 Team: %s"), *(bIsPlayer0TeamA ? FString("TeamA") : FString("TeamB")));
}

void ALCGameMode::BeginGame()
{
}

void ALCGameMode::EndGame()
{
}


void ALCGameMode::CheckAllPlayersReady()
{
	if (bIsAllPlayerJoined && !bIsReadyToPlay && !bIsGamePlaying)
	{
		const bool bIsPlayer0ReadyForInitGame = Player0->IsPlayerReadyForInitGame();
		const bool bIsPlayer1ReadyForInitGame = Player1->IsPlayerReadyForInitGame();

		// Both player valid, init game
		if (bIsPlayer0ReadyForInitGame && bIsPlayer1ReadyForInitGame)
		{
			// Clear timer no need to run timer
			PendingReadyTimeElapsed = 0.0f;
			GetWorldTimerManager().ClearTimer(TimerHandle_ClientGameState);
			bIsReadyToPlay = true;
			UE_LOG(LogTemp, Log, TEXT("Both Players Ready"));
			InitGame(EBoardSetup::EBS_ACE);
		}
		else
		{
			PendingReadyTimeElapsed +=PlayerReadyCheckFrequency;
			bIsReadyToPlay = false;

			if(PendingReadyTimeElapsed > MaxPlayerPendingReady)
			{
				NotifyAuthorityPlayerPendingReady();
			}
		}
	}
}

void ALCGameMode::InvalidateSecondPlayer()
{
	Player1 = nullptr;
	bIsAllPlayerJoined = false;
	bIsReadyToPlay = false;
}

void ALCGameMode::InitLaserChessAI(FLaserChessAIInitParam InitParams)
{
	UE_LOG(LogLaserChess, Log, TEXT("Gameplay Offline Opponent is AI."));
}

void ALCGameMode::NotifyAuthorityPlayerPendingReady()
{
	// TODO: Should open UI for Listen Server.

	HandleJoinedPlayerNotReady();
}

void ALCGameMode::HandleAllPlayerJoined()
{
	PendingReadyTimeElapsed = 0.0f;
	
	// Check if game state are valid
	GetWorldTimerManager().SetTimer(TimerHandle_ClientGameState, this, &ALCGameMode::CheckAllPlayersReady,
		PlayerReadyCheckFrequency, true);	
}

void ALCGameMode::HandleJoinedPlayerNotReady()
{
	const bool bIsPlayer0ReadyForInitGame = Player0->IsPlayerReadyForInitGame();
	const bool bIsPlayer1ReadyForInitGame = Player1->IsPlayerReadyForInitGame();
	
	// Player0 is ready but Player1 is not
	if(bIsPlayer0ReadyForInitGame && !bIsPlayer1ReadyForInitGame)
	{
		LCGameSessionRef->KickPlayer(Player1, FText::FromString("Player Not Ready, Time Expired."));
		InvalidateSecondPlayer();
	}

	// Player1 is ready but Player0 is not
	if(!bIsPlayer0ReadyForInitGame && bIsPlayer1ReadyForInitGame)
	{
		LCGameSessionRef->KickPlayer(Player0, FText::FromString("Player Not Ready, Time Expired."));
        Player0 = Player1; // Move player 0 to player 1
		InvalidateSecondPlayer();
	}
}

