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
	
	/** Return camera pawn type its controlling. */
	FORCEINLINE class ALCCameraPawn* GetCameraPawn() const { return ControlledCameraPawnRef; }

	/** Return laser chess game state reference. */
	FORCEINLINE class ALCGameState* GetLCGameState() const { return LaserChessGameStateRef; }
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Server and Client Functions


protected:
	/** Sync client has game state to servers */
	UFUNCTION(Server, Reliable)
	void SyncToClientGameState(bool bState);
};
