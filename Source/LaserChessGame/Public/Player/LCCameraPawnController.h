// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LCCameraPawnController.generated.h"

enum class EPawnTeam : uint8;

/**
 * 
 */
UCLASS()
class LASERCHESSGAME_API ALCCameraPawnController : public APlayerController
{
	GENERATED_BODY()

private:
	/** Camera pawn ref that is being used */
	UPROPERTY(VisibleAnywhere, Replicated)
	class ALCCameraPawn* ControlledCameraPawnRef;

	/** Laser Chess Game state reference */
	UPROPERTY(VisibleAnywhere)
	class ALCGameState* LaserChessGameStateRef;

	/** Player pawn playing team */
	UPROPERTY(VisibleAnywhere, Replicated)
	EPawnTeam PawnTeam;
	
	/** True if this player has a valid game state */
	UPROPERTY(VisibleAnywhere)
	uint8 bHasValidGameStateOnClient : 1;

	/** How frequently ClientGameStatePawnTileRegister will be updated */
	UPROPERTY(EditDefaultsOnly, Category= "Pawn Update Rate")
	float PawnTileRegistrationUpdate;
	
	/** Client Game state Pawn and Tile Register timer */
	FTimerHandle TimeHandle_ClientGameStatePawnTileRegister;
	
protected:
	ALCCameraPawnController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void OnPossess(class APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Called when player controller is ready, Runs only for Listen Server and clients. */
	void OnPlayerControllerReady();

public:

	/** When called reset player camera to initial rotation. */
	void ResetCamera();

	/** When called center in game mouse cursor */
	void CenterMouseCursor();
	
	/** Runs on client to check if a valid game state exists on respective clients. */
	bool HasValidGameStateOnClient() const { return bHasValidGameStateOnClient; }

	/*** Return true if this player is ready. so server can initialize LaserChessGame. */
	bool IsPlayerReadyForInitGame() const;
	
	/** Return camera pawn type its controlling. */
	FORCEINLINE class ALCCameraPawn* GetCameraPawn() const { return ControlledCameraPawnRef; }

	/** Return laser chess game state reference. */
	FORCEINLINE class ALCGameState* GetLCGameState() const { return LaserChessGameStateRef; }
	
	/** Return whet team player has chosen.
	 * Only works if the game is offline,
	 * or in case of online game this pawn is a listen server of first to join.
	*/
	EPawnTeam GetPlayerChosenTeam() const;
	
	/** Return current pawn team */
	UFUNCTION()
	EPawnTeam GetTeam() const { return PawnTeam; }

	/** Server function, Must be called on server, Set Pawn team on Server + owning client. */
	UFUNCTION()
	void SetServerPawnTeam(EPawnTeam NewTeam);
	
protected:

	/** Called on a timer to find all pawns and tiles for client version of game state  */
	UFUNCTION()
	void ClientGameStatePawnTileRegister();
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Server and Client Functions

	/** Sync client has game state to servers */
	UFUNCTION(Server, Reliable)
	void SyncToClientGameState(bool bState);

	/** Set pawn tem on client, must be called from server */
	UFUNCTION(Client, reliable)
	void SetClientPawnTeam(EPawnTeam NewTeam);
};
