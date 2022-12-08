// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Online/LCGameState.h"
#include "Online/LCGameMode.h"
#include "Game/LaserChessGameTypes.h"
#include "Game/LaserChessPawnSpawnData.h"
#include "Game/LCBoardTile.h"
#include "Game/LCBoardPawn.h"

ALCGameState::ALCGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TileSize = 100.0f;
}

void ALCGameState::BeginPlay()
{
	Super::BeginPlay();

	// Check is server version
	if (GetLocalRole() == ROLE_Authority)
	{
		ServerGameMode = Cast<ALCGameMode>(AuthorityGameMode);
		if (ServerGameMode)
		{
			UE_LOG(LogLaserChess, Log, TEXT("Laser Chess Game State: Authority Game Mode is Server Game Mode"));

			// @TODO: Should be called on game mode
			SpawnGameTilesServer();
			SpawnGamePawnServer(EBoardSetup::EBS_ACE);
		}
	}
}

void ALCGameState::SpawnGameTilesServer()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		UE_LOG(LogLaserChess, Log, TEXT("Game State server spawining a chess board of size, Rows: %d and Columns %d"), LC_BOARD_ROWS, LC_BOARD_COLUMNS);
		//EventActiveBoardTiles.SetNum(8);

		if (BoardTileClass)
		{
			FActorSpawnParameters TileSpawnParams;
			TileSpawnParams.Owner = this;
			TileSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			FVector BottomLeft(0.0f);
			BottomLeft.X -= LC_BOARD_ROWS * TileSize * 0.5f;
			BottomLeft.Y -= LC_BOARD_COLUMNS * TileSize * 0.5f;

			for (uint8 r = 0; r < LC_BOARD_ROWS; r++)
			{
				for (uint8 c = 0; c < LC_BOARD_COLUMNS; c++)
				{
					FVector SpawnLocation = BottomLeft;
					SpawnLocation.X += (2 * r + 1) * TileSize * 0.5f;
					SpawnLocation.Y += (2 * c + 1) * TileSize * 0.5f;
					
					if (ALCBoardTile* SpawnedTile = GetWorld()->SpawnActor<ALCBoardTile>(BoardTileClass, SpawnLocation, FRotator::ZeroRotator, TileSpawnParams))
					{
						BoardTiles.Add(SpawnedTile);
						SpawnedTile->InitServerBoardTile(r, c);
					}
				}
			}
		}

		UE_LOG(LogLaserChess, Log, TEXT("Server Game State Tiles: %d"), BoardTiles.Num());
	}
}

void ALCGameState::SpawnGamePawnServer(EBoardSetup Setup)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		UE_LOG(LogLaserChess, Log, TEXT("Game State server spawining a chess board pieces"));

		if(BoardPawnClass)
		{
			// Board setup
			FBoardPawnSetup BoardPawnSetup;
			switch (Setup)
			{
				case EBoardSetup::EBS_ACE:			BoardPawnSetup = BoardSetup::Ace();			break;
				case EBoardSetup::EBS_CURIOSITY:	BoardPawnSetup = BoardSetup::Curiosity();	break;
				case EBoardSetup::EBS_GRAIL:		BoardPawnSetup = BoardSetup::Grail();		break;
				case EBoardSetup::EBS_MERCURY:		BoardPawnSetup = BoardSetup::Mercury();		break;
				case EBoardSetup::EBS_SOPHIE:		BoardPawnSetup = BoardSetup::Sophie();		break;
			default:
				UE_LOG(LogLaserChess, Log, TEXT("Invalid board setup."));
				return;
			}

			FActorSpawnParameters PawnSpawnParams;
			PawnSpawnParams.Owner = this;
			PawnSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Spawn Laser Pawn Pieces
			for (int i = 0; i < LC_BOARD_PAWN_COUNT_LASER; i++)
			{
				const FPawnSpawnData _SpawnData = BoardPawnSetup.LaserPawn[i];
				class ALCBoardPawn* LaserChessPawn = GetWorld()->SpawnActor<ALCBoardPawn>(BoardPawnClass, FVector::ZeroVector, FRotator(0.0f, _SpawnData.PawnSpawnYaw, 0.0f), PawnSpawnParams);
				LaserChessPawn->InitServerBoardPawn(GetTileByRowColumn(_SpawnData.RowIndex, _SpawnData.ColumnIndex), BoardPawns.Num(), _SpawnData.bIsTeamA, EPawnType::EPT_Laser);
				BoardPawns.Add(LaserChessPawn);
			}

			// Spawn King Pawn Pieces
			for (int i = 0; i < LC_BOARD_PAWN_COUNT_KING; i++)
			{
				const FPawnSpawnData _SpawnData = BoardPawnSetup.KingPawn[i];
				class ALCBoardPawn* LaserChessPawn = GetWorld()->SpawnActor<ALCBoardPawn>(BoardPawnClass, FVector::ZeroVector, FRotator(0.0f, _SpawnData.PawnSpawnYaw, 0.0f), PawnSpawnParams);
				LaserChessPawn->InitServerBoardPawn(GetTileByRowColumn(_SpawnData.RowIndex, _SpawnData.ColumnIndex), BoardPawns.Num(), _SpawnData.bIsTeamA, EPawnType::EPT_King);
				BoardPawns.Add(LaserChessPawn);
			}

			// Spawn Switch Pawn Pieces
			for (int i = 0; i < LC_BOARD_PAWN_COUNT_SWITCH; i++)
			{
				const FPawnSpawnData _SpawnData = BoardPawnSetup.SwitchPawn[i];
				class ALCBoardPawn* LaserChessPawn = GetWorld()->SpawnActor<ALCBoardPawn>(BoardPawnClass, FVector::ZeroVector, FRotator(0.0f, _SpawnData.PawnSpawnYaw, 0.0f), PawnSpawnParams);
				LaserChessPawn->InitServerBoardPawn(GetTileByRowColumn(_SpawnData.RowIndex, _SpawnData.ColumnIndex), BoardPawns.Num(), _SpawnData.bIsTeamA, EPawnType::EPT_Switch);
				BoardPawns.Add(LaserChessPawn);
			}
			
			// Spawn Defender Pawn Pieces
			for (int i = 0; i < LC_BOARD_PAWN_COUNT_DEFENDER; i++)
			{
				const FPawnSpawnData _SpawnData = BoardPawnSetup.DefenderPawn[i];
				class ALCBoardPawn* LaserChessPawn = GetWorld()->SpawnActor<ALCBoardPawn>(BoardPawnClass, FVector::ZeroVector, FRotator(0.0f, _SpawnData.PawnSpawnYaw, 0.0f), PawnSpawnParams);
				LaserChessPawn->InitServerBoardPawn(GetTileByRowColumn(_SpawnData.RowIndex, _SpawnData.ColumnIndex), BoardPawns.Num(), _SpawnData.bIsTeamA, EPawnType::EPT_Defender);
				BoardPawns.Add(LaserChessPawn);
			}

			// Spawn Deflector Pawn Pieces
			for (int i = 0; i < LC_BOARD_PAWN_COUNT_DEFLECTOR; i++)
			{
				const FPawnSpawnData _SpawnData = BoardPawnSetup.DeflectorPawn[i];
				class ALCBoardPawn* LaserChessPawn = GetWorld()->SpawnActor<ALCBoardPawn>(BoardPawnClass, FVector::ZeroVector, FRotator(0.0f, _SpawnData.PawnSpawnYaw, 0.0f), PawnSpawnParams);
				LaserChessPawn->InitServerBoardPawn(GetTileByRowColumn(_SpawnData.RowIndex, _SpawnData.ColumnIndex), BoardPawns.Num(), _SpawnData.bIsTeamA, EPawnType::EPT_Deflector);
				BoardPawns.Add(LaserChessPawn);
			}
		}
	}
}

ALCBoardTile* ALCGameState::GetTileByRowColumn(int32 RowIndex, int32 ColumnIndex) const
{
	int32 Index;
	if(LCHelperFunc::GetIndexFromRowColumn(RowIndex, ColumnIndex, Index))
	{
		return BoardTiles[Index];
	}

	return nullptr;
}

ALCBoardTile* ALCGameState::GetTileByIndex(int32 Index) const
{
	return BoardTiles.IsValidIndex(Index) ? BoardTiles[Index] : nullptr;
}

ALCBoardPawn* ALCGameState::GetPawnByIndex(int32 Index) const
{
	return BoardPawns.IsValidIndex(Index) ? BoardPawns[Index] : nullptr;;
}
