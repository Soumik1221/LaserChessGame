// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LCBoardPawn.generated.h"

UCLASS()
class LASERCHESSGAME_API ALCBoardPawn : public AActor
{
	GENERATED_BODY()

	/** Board tile scene root component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USceneComponent> PawnRoot;

	/** Board tile static mesh component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UStaticMeshComponent> PawnMesh;

protected:
	/** Laser chess pawn Index */
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Data")
	uint8 PawnIndex;

	/** Laser chess pawn type */
	UPROPERTY(ReplicatedUsing = OnRep_PawnType, VisibleAnywhere, Category = "Data")
	EPawnType PawnType;

	/** Laser chess pawn team */
	UPROPERTY(ReplicatedUsing = OnRep_PawnTeam, VisibleAnywhere, Category = "Data")
	EPawnTeam PawnTeam;

	/** Tile that this pawn is placed */
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Data")
	TObjectPtr<class ALCBoardTile> TileRef;
	
	/** Owner Game state  */
	UPROPERTY(VisibleAnywhere, Category = "Data")
	TObjectPtr<class ALCGameState> GameStateOwner;
protected:
	ALCBoardPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

	/** Update tile color to reflect tile type */
	UFUNCTION(BlueprintImplementableEvent, Category = "Pawn")
	void OnPawnTypeChanged(EPawnType OutType);

	/** Update tile color to reflect tile type */
	UFUNCTION(BlueprintImplementableEvent, Category = "Pawn")
	void OnPawnTeamChanged(EPawnTeam OutTeam);

	/** Called to replicate pawn type */
	UFUNCTION()
	void OnRep_PawnType(EPawnType OldType);

	/** Called to replicate pawn team */
	UFUNCTION()
	void OnRep_PawnTeam(EPawnTeam OldTeam);
	
public:
	/** Initialize board pawn */
	void InitServerBoardPawn(class ALCBoardTile* InTile, int32 InIndex, bool bIsTeamA, EPawnType InType);
	
	/** Set tile this piece is on. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void SetTile(class ALCBoardTile* InTile);
	
	/** Return what tile this piece is on. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	class ALCBoardTile* GetTile() const { return TileRef; }
	
	/** Return spawn Index of this tile */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	uint8 GetIndex() const { return PawnIndex; }
	
	/** Return what type of pawn is this. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	EPawnType GetPawnType() const { return PawnType;  }

	/** Return what team this pawn belongs to. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	EPawnTeam GetPawnTeam() const { return PawnTeam;  }
};

