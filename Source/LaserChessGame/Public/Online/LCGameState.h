// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LaserChessGame.h"
#include "LCGameState.generated.h"

enum class EBoardSetup :uint8;
enum class EPawnType :uint8;
enum class EPawnTeam :uint8;

/**
 * 
 */
UCLASS()
class LASERCHESSGAME_API ALCGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	/** Laser chess board tile class. */
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<class ALCBoardTile> BoardTileClass;

	/** Laser Chess board pawn class. */
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<class ALCBoardPawn> BoardPawnClass;
	
	/** Laser chess board tile class. */
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	float TileSize;
	
private:
	/** Game mode reference of the server [Only available to the server version of game state] */
	UPROPERTY()
	class ALCGameMode* ServerGameMode;

	/** All spawned board tiles */
	TArray<class ALCBoardTile*, TFixedAllocator<LC_BOARD_ROWS * LC_BOARD_COLUMNS>> BoardTiles;

	/** All spawned board pawn pieces */
	TArray<class ALCBoardPawn*, TFixedAllocator<LC_BOARD_Pawns>> BoardPawns;

protected:
	ALCGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

public:
	/** Spawn laser chess game board tiles on server. */
	void SpawnGameTilesServer();

	/** Spawn laser chess game board pawn pieces based on board setup. */
	void SpawnGamePawnServer(EBoardSetup Setup);

	/** Return tile that exists in given row and column index */
	UFUNCTION(BlueprintCallable, Category = "Laser Chess")
	FORCEINLINE class ALCBoardTile* GetTileByRowColumn(int32 RowIndex, int32 ColumnIndex) const;

	/** Return tile that exists in given index */
	UFUNCTION(BlueprintCallable, Category = "Laser Chess")
	FORCEINLINE class ALCBoardTile* GetTileByIndex(int32 Index) const;

	/** Return pawn that exists in given index */
	UFUNCTION(BlueprintCallable, Category = "Laser Chess")
	FORCEINLINE class ALCBoardPawn* GetPawnByIndex(int32 Index) const;
};
