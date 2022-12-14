// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Game/LCBoardTile.h"
#include "Game/LaserChessGameTypes.h"
#include "Online/LCGameState.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LaserChessGame.h"
#include "Net/UnrealNetwork.h"

ALCBoardTile::ALCBoardTile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TileRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("TileRootComp"));
	RootComponent = TileRoot;

	TileMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TileMeshComp"));
	TileMesh->SetupAttachment(TileRoot);

	PrimaryActorTick.bCanEverTick = false;
	bAlwaysRelevant = true;
	bReplicates = true;

	TileType = ETileType::ETT_Both;
}

void ALCBoardTile::BeginPlay()
{
	Super::BeginPlay();
	GameStateOwner = GetWorld()->GetGameState<ALCGameState>();
}

void ALCBoardTile::OnRep_TileType(ETileType OldType)
{
	// Tile type changed
	if(TileType != OldType)
	{
		OnTileTypeChanged(TileType);
	}
}

void ALCBoardTile::InitServerBoardTile(uint8 RowIndex, uint8 ColumnIndex)
{
	// Set tile type
	if(RowIndex < LC_BOARD_ROWS && ColumnIndex < LC_BOARD_COLUMNS)
	{
		RowIndex++;
		ColumnIndex++;
		if (ColumnIndex <= 2)
		{
			if (ColumnIndex == 2 && (RowIndex == 1 || RowIndex == LC_BOARD_ROWS))
			{
				TileType = ETileType::ETT_TeamB;
			}
			else if (ColumnIndex == 1)
				TileType = RowIndex == LC_BOARD_ROWS ? ETileType::ETT_Laser : ETileType::ETT_TeamA;
		}
		else if (ColumnIndex >= LC_BOARD_COLUMNS - 1)
		{
			if (ColumnIndex == LC_BOARD_COLUMNS - 1 && (RowIndex == 1 || RowIndex == LC_BOARD_ROWS))
			{
				TileType = ETileType::ETT_TeamA;
			}
			else if(ColumnIndex == LC_BOARD_COLUMNS)
				TileType = RowIndex == 1 ? ETileType::ETT_Laser : ETileType::ETT_TeamB;
		}

		// For standalone and listen server update immediately
		if(GetNetMode() == NM_Standalone || GetNetMode() == NM_ListenServer)
		{
			OnTileTypeChanged(TileType);
		}
	}
}

void ALCBoardTile::UpdateTilesVisualsForClients()
{
	// Only update for both tiles as they are not updated because TileType does not changed.
	if(TileType == ETileType::ETT_Both)
	{
		OnTileTypeChanged(TileType);
	}
}

void ALCBoardTile::SetPawn(ALCBoardPawn* InPawn)
{
	if(PawnRef != InPawn)
	{
		PawnRef = InPawn;
		// @TODO: Update Tile action active inactive state
	}
}

void ALCBoardTile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALCBoardTile, TileIndex);
	DOREPLIFETIME(ALCBoardTile, TileType);
	DOREPLIFETIME(ALCBoardTile, PawnRef);
}
