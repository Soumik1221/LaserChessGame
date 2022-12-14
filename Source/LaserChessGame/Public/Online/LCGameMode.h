// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LCGameMode.generated.h"

enum class EBoardSetup : uint8;
enum class EPawnTeam : uint8;
// TODO: This should be inside AI system. Just forward declare it
struct FLaserChessAIInitParam
{};
/**
 * 
 */
UCLASS()
class LASERCHESSGAME_API ALCGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	/** Player 0 and 1 as they joined the game */
	UPROPERTY()
	TObjectPtr<class ALCCameraPawnController> Player0;
	UPROPERTY()
	TObjectPtr<class ALCCameraPawnController> Player1;

	/** Laser chess game state reference */
	UPROPERTY()
	TObjectPtr<class ALCGameState> LCGameStateRef;

	/** Laser chess game session reference */
	UPROPERTY()
	TObjectPtr<class ALCGameSession> LCGameSessionRef;
	
	/** Check if game is launched as offline  */
	uint8 bIsOfflineGame : 1;
	
	/** True if player 0 is Team A */
	UPROPERTY()
	uint8 bIsPlayer0TeamA : 1;
	
	/** Is all player joined */
	UPROPERTY(VisibleAnywhere)
	uint8 bIsAllPlayerJoined : 1;

	/** Game ready to be played */
	UPROPERTY(VisibleAnywhere)
	uint8 bIsReadyToPlay : 1;

	/** Game is initialized to be played. */
	UPROPERTY(VisibleAnywhere)
	uint8 bIsGameInitialized : 1;

	/** Game is currently playing */
	UPROPERTY(VisibleAnywhere)
	uint8 bIsGamePlaying : 1;

	/** How often CheckPlayersReady function should be called. */
	UPROPERTY(EditDefaultsOnly, Category = "Laser Chess Game")
	float PlayerReadyCheckFrequency;

	/** How much time game mode should wait for player to be ready. */
	UPROPERTY(EditDefaultsOnly, Category = "Laser Chess Game")
	float MaxPlayerPendingReady;
	
	/** Current board setup */
	UPROPERTY()
	EBoardSetup BoardSetup;

	/** Team that is currently playing */
	UPROPERTY()
	EPawnTeam CurrentPlayingTeam;

	// Timer handle for checking clients has valid game state
	FTimerHandle TimerHandle_ClientGameState;

	/** How much time elapsed since player joined but pending for them tobe ready */
	float PendingReadyTimeElapsed;
protected:
	ALCGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
	/** Initialize Laser chess game to be played */
	UFUNCTION()
	void InitGame(EBoardSetup InSetup);

	/** Begin a Laser Chess Game */
	UFUNCTION()
	void BeginGame();

	/** Finish a Laser Chess Game */
	UFUNCTION()
	void EndGame();
	
	/** Check is all player worlds are ready to begin game */
	UFUNCTION()
	void CheckAllPlayersReady();

	/** Invalidate second player and re-open for new player joining */
	void InvalidateSecondPlayer();
	
	/** Initialize laser chess game AI (For offline game only)*/
	//UFUNCTION()
	void InitLaserChessAI(FLaserChessAIInitParam InitParams);

	/** Notify correct authority that joined players are still not ready although max time passed */
	UFUNCTION()
	void NotifyAuthorityPlayerPendingReady();
	
	/** Handler function called when all player have been joined. */
	UFUNCTION()
	void HandleAllPlayerJoined();

	/** Handle joined players are still not ready although max time passed.
	 *
	 * If player 0 is not ready kick it out and open for new player to be joined. Also shift player 1 as player 0
	 * If player 1 is not ready kick it out and open for new player to be joined
	 */
	void HandleJoinedPlayerNotReady();
};
