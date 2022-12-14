// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LCBoardTile.generated.h"

UCLASS()
class LASERCHESSGAME_API ALCBoardTile : public AActor
{
	GENERATED_BODY()
private:
	/** Board tile scene root component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USceneComponent> TileRoot;

	/** Board tile static mesh component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UStaticMeshComponent> TileMesh;

	
protected:
	/** Spawn Index of this tile */
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Data")
	uint8 TileIndex;

	/** What type of tile is this */
	UPROPERTY(ReplicatedUsing= OnRep_TileType, VisibleAnywhere, Category = "Data")
	ETileType TileType;

	/** Pawn that this tile is placed */
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Data")
	TObjectPtr<class ALCBoardPawn> PawnRef;
	
	/** Owner Game state  */
	UPROPERTY(VisibleAnywhere, Category = "Data")
	TObjectPtr<class ALCGameState> GameStateOwner;
	
protected:
	ALCBoardTile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

	/** Update tile color to reflect tile type */
	UFUNCTION(BlueprintImplementableEvent, Category = "Tile")
	void OnTileTypeChanged(ETileType OutType);

	/** Called to replicate tile type */
	UFUNCTION()
	void OnRep_TileType(ETileType OldType);
	
public:
	/** Initialize board tile [Server] */
	void InitServerBoardTile(uint8 RowIndex, uint8 ColumnIndex);

	/** Called only for clients to update their visuals */
	void UpdateTilesVisualsForClients();
	
	/** Return what pawn this tile is holding. */
	UFUNCTION(BlueprintCallable, Category = "Tile")
	class ALCBoardPawn* GetPawn() const { return PawnRef; }

	/** Set pawn that this tile is holding */
	void SetPawn(class ALCBoardPawn* InPawn);
	
	/** Return spawn Index of this tile */
	UFUNCTION(BlueprintCallable, Category = "Tile")
	uint8 GetIndex() const { return TileIndex; }

	/** Return what type of tile is this */
	UFUNCTION(BlueprintCallable, Category = "Tile")
	ETileType GetTileType() const { return TileType; }
};
