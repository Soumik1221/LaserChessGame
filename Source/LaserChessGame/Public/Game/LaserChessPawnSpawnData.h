#pragma once

#include "LaserChessPawnSpawnData.generated.h"


/** Lase Chess pawn initial spawn data */
USTRUCT(BlueprintType)
struct FPawnSpawnData
{
    GENERATED_BODY()

    /** Spawn row indexes [zero base] */
    UPROPERTY(EditDefaultsOnly)
    int RowIndex;

    /** Spawn column indexes [zero base] */
    UPROPERTY(EditDefaultsOnly)
    int ColumnIndex;

    /** pawn spawn yaws */
    UPROPERTY(EditDefaultsOnly)
    float PawnSpawnYaw;

    /** True = Team A, false = Team B */
    UPROPERTY(EditDefaultsOnly)
    bool bIsTeamA;
};

/** Piece location information for each piece */
USTRUCT(BlueprintType)
struct FBoardPawnSetup
{
    GENERATED_BODY()

    /** Laser piece spawn */
    UPROPERTY(EditDefaultsOnly, Category = "Data")
    FPawnSpawnData LaserPawn[2];

    /** King piece spawn */
    UPROPERTY(EditDefaultsOnly, Category = "Data")
    FPawnSpawnData KingPawn[2];

    /** Switch piece spawn */
    UPROPERTY(EditDefaultsOnly, Category = "Data")
    FPawnSpawnData SwitchPawn[4];

    /** Defender piece spawn */
    UPROPERTY(EditDefaultsOnly, Category = "Data")
    FPawnSpawnData DefenderPawn[4];

    /** Deflector piece spawn */
    UPROPERTY(EditDefaultsOnly, Category = "Data")
    FPawnSpawnData DeflectorPawn[14];
};


namespace BoardSetup
{
	// Ace Setup
	static FBoardPawnSetup Ace()
	{
		FBoardPawnSetup BoardPawnSetup;
		// Laser setup
		BoardPawnSetup.LaserPawn[0].bIsTeamA = true;
		BoardPawnSetup.LaserPawn[0].RowIndex = 7;
		BoardPawnSetup.LaserPawn[0].ColumnIndex = 0;
		BoardPawnSetup.LaserPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.LaserPawn[1].bIsTeamA = false;
		BoardPawnSetup.LaserPawn[1].RowIndex = 0;
		BoardPawnSetup.LaserPawn[1].ColumnIndex = 9;
		BoardPawnSetup.LaserPawn[1].PawnSpawnYaw = -90.0f;
	
		// King setup
		BoardPawnSetup.KingPawn[0].bIsTeamA = true;
		BoardPawnSetup.KingPawn[0].RowIndex = 7;
		BoardPawnSetup.KingPawn[0].ColumnIndex = 5;
		BoardPawnSetup.KingPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.KingPawn[1].bIsTeamA = false;
		BoardPawnSetup.KingPawn[1].RowIndex = 0;
		BoardPawnSetup.KingPawn[1].ColumnIndex = 4;
		BoardPawnSetup.KingPawn[1].PawnSpawnYaw = 0.0f;
	
		// Defender setup
		BoardPawnSetup.DefenderPawn[0].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[0].RowIndex = 7;
		BoardPawnSetup.DefenderPawn[0].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[0].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[1].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[1].RowIndex = 7;
		BoardPawnSetup.DefenderPawn[1].ColumnIndex = 6;
		BoardPawnSetup.DefenderPawn[1].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[2].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[2].RowIndex = 0;
		BoardPawnSetup.DefenderPawn[2].ColumnIndex = 3;
		BoardPawnSetup.DefenderPawn[2].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DefenderPawn[3].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[3].RowIndex = 0;
		BoardPawnSetup.DefenderPawn[3].ColumnIndex = 5;
		BoardPawnSetup.DefenderPawn[3].PawnSpawnYaw = 0.0f;
	
		//Switch setup
		BoardPawnSetup.SwitchPawn[0].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[0].RowIndex = 4;
		BoardPawnSetup.SwitchPawn[0].ColumnIndex = 4;
		BoardPawnSetup.SwitchPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.SwitchPawn[1].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[1].RowIndex = 4;
		BoardPawnSetup.SwitchPawn[1].ColumnIndex = 5;
		BoardPawnSetup.SwitchPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[2].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[2].RowIndex = 3;
		BoardPawnSetup.SwitchPawn[2].ColumnIndex = 4;
		BoardPawnSetup.SwitchPawn[2].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[3].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[3].RowIndex = 3;
		BoardPawnSetup.SwitchPawn[3].ColumnIndex = 5;
		BoardPawnSetup.SwitchPawn[3].PawnSpawnYaw = 0.0f;
	
		// Deflector setup
		BoardPawnSetup.DeflectorPawn[0].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[0].RowIndex = 7;
		BoardPawnSetup.DeflectorPawn[0].ColumnIndex = 7;
		BoardPawnSetup.DeflectorPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[1].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[1].RowIndex = 6;
		BoardPawnSetup.DeflectorPawn[1].ColumnIndex = 2;
		BoardPawnSetup.DeflectorPawn[1].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[2].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[2].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[2].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[2].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[3].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[3].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[3].ColumnIndex = 7;
		BoardPawnSetup.DeflectorPawn[3].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[4].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[4].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[4].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[4].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[5].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[5].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[5].ColumnIndex = 7;
		BoardPawnSetup.DeflectorPawn[5].PawnSpawnYaw = 0.0f;
	
	
		BoardPawnSetup.DeflectorPawn[6].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[6].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[6].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[6].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[7].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[7].RowIndex = 0;
		BoardPawnSetup.DeflectorPawn[7].ColumnIndex = 2;
		BoardPawnSetup.DeflectorPawn[7].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[8].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[8].RowIndex = 1;
		BoardPawnSetup.DeflectorPawn[8].ColumnIndex = 7;
		BoardPawnSetup.DeflectorPawn[8].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[9].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[9].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[9].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[9].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[10].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[10].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[10].ColumnIndex = 2;
		BoardPawnSetup.DeflectorPawn[10].PawnSpawnYaw = -90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[11].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[11].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[11].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[11].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[12].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[12].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[12].ColumnIndex = 2;
		BoardPawnSetup.DeflectorPawn[12].PawnSpawnYaw = 180.0f;
	
	
		BoardPawnSetup.DeflectorPawn[13].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[13].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[13].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[13].PawnSpawnYaw = -90.0f;
	
		return BoardPawnSetup;
	}
		
	// Curiosity Setup
	static FBoardPawnSetup Curiosity()
	{
		FBoardPawnSetup BoardPawnSetup;
		// Laser setup
		BoardPawnSetup.LaserPawn[0].bIsTeamA = true;
		BoardPawnSetup.LaserPawn[0].RowIndex = 7;
		BoardPawnSetup.LaserPawn[0].ColumnIndex = 0;
		BoardPawnSetup.LaserPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.LaserPawn[1].bIsTeamA = false;
		BoardPawnSetup.LaserPawn[1].RowIndex = 0;
		BoardPawnSetup.LaserPawn[1].ColumnIndex = 9;
		BoardPawnSetup.LaserPawn[1].PawnSpawnYaw = -90.0f;
		
		// King setup
		BoardPawnSetup.KingPawn[0].bIsTeamA = true;
		BoardPawnSetup.KingPawn[0].RowIndex = 7;
		BoardPawnSetup.KingPawn[0].ColumnIndex = 5;
		BoardPawnSetup.KingPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.KingPawn[1].bIsTeamA = false;
		BoardPawnSetup.KingPawn[1].RowIndex = 0;
		BoardPawnSetup.KingPawn[1].ColumnIndex = 4;
		BoardPawnSetup.KingPawn[1].PawnSpawnYaw = 0.0f;
	
		// Defender setup
		BoardPawnSetup.DefenderPawn[0].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[0].RowIndex = 7;
		BoardPawnSetup.DefenderPawn[0].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[0].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[1].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[1].RowIndex = 7;
		BoardPawnSetup.DefenderPawn[1].ColumnIndex = 6;
		BoardPawnSetup.DefenderPawn[1].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[2].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[2].RowIndex = 0;
		BoardPawnSetup.DefenderPawn[2].ColumnIndex = 3;
		BoardPawnSetup.DefenderPawn[2].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DefenderPawn[3].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[3].RowIndex = 0;
		BoardPawnSetup.DefenderPawn[3].ColumnIndex = 5;
		BoardPawnSetup.DefenderPawn[3].PawnSpawnYaw = 0.0f;
	
		//Switch setup
		BoardPawnSetup.SwitchPawn[0].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[0].RowIndex = 7;
		BoardPawnSetup.SwitchPawn[0].ColumnIndex = 7;
		BoardPawnSetup.SwitchPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[1].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[1].RowIndex = 4;
		BoardPawnSetup.SwitchPawn[1].ColumnIndex = 5;
		BoardPawnSetup.SwitchPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[2].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[2].RowIndex = 0;
		BoardPawnSetup.SwitchPawn[2].ColumnIndex = 2;
		BoardPawnSetup.SwitchPawn[2].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[3].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[3].RowIndex = 3;
		BoardPawnSetup.SwitchPawn[3].ColumnIndex = 4;
		BoardPawnSetup.SwitchPawn[3].PawnSpawnYaw = 90.0f;
	
		// Deflector setup
		BoardPawnSetup.DeflectorPawn[0].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[0].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[0].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[1].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[1].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[1].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[1].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[2].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[2].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[2].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[2].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[3].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[3].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[3].ColumnIndex = 8;
		BoardPawnSetup.DeflectorPawn[3].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[4].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[4].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[4].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[4].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[5].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[5].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[5].ColumnIndex = 8;
		BoardPawnSetup.DeflectorPawn[5].PawnSpawnYaw = 0.0f;
	
	
		BoardPawnSetup.DeflectorPawn[6].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[6].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[6].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[6].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[7].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[7].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[7].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[7].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[8].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[8].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[8].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[8].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[9].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[9].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[9].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[9].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[10].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[10].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[10].ColumnIndex = 1;
		BoardPawnSetup.DeflectorPawn[10].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[11].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[11].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[11].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[11].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[12].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[12].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[12].ColumnIndex = 1;
		BoardPawnSetup.DeflectorPawn[12].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[13].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[13].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[13].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[13].PawnSpawnYaw = -90.0f;
	
		return BoardPawnSetup;
	}
			
	// Grail Setup
	static FBoardPawnSetup Grail()
	{
		FBoardPawnSetup BoardPawnSetup;
		// Laser setup
		BoardPawnSetup.LaserPawn[0].bIsTeamA = true;
		BoardPawnSetup.LaserPawn[0].RowIndex = 7;
		BoardPawnSetup.LaserPawn[0].ColumnIndex = 0;
		BoardPawnSetup.LaserPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.LaserPawn[1].bIsTeamA = false;
		BoardPawnSetup.LaserPawn[1].RowIndex = 0;
		BoardPawnSetup.LaserPawn[1].ColumnIndex = 9;
		BoardPawnSetup.LaserPawn[1].PawnSpawnYaw = -90.0f;
	
		// King setup
		BoardPawnSetup.KingPawn[0].bIsTeamA = true;
		BoardPawnSetup.KingPawn[0].RowIndex = 6;
		BoardPawnSetup.KingPawn[0].ColumnIndex = 5;
		BoardPawnSetup.KingPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.KingPawn[1].bIsTeamA = false;
		BoardPawnSetup.KingPawn[1].RowIndex = 1;
		BoardPawnSetup.KingPawn[1].ColumnIndex = 4;
		BoardPawnSetup.KingPawn[1].PawnSpawnYaw = 0.0f;
	
		// Defender setup
		BoardPawnSetup.DefenderPawn[0].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[0].RowIndex = 7;
		BoardPawnSetup.DefenderPawn[0].ColumnIndex = 5;
		BoardPawnSetup.DefenderPawn[0].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[1].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[1].RowIndex = 5;
		BoardPawnSetup.DefenderPawn[1].ColumnIndex = 5;
		BoardPawnSetup.DefenderPawn[1].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[2].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[2].RowIndex = 0;
		BoardPawnSetup.DefenderPawn[2].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[2].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DefenderPawn[3].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[3].RowIndex = 2;
		BoardPawnSetup.DefenderPawn[3].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[3].PawnSpawnYaw = 0.0f;
	
		//Switch setup
		BoardPawnSetup.SwitchPawn[0].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[0].RowIndex = 5;
		BoardPawnSetup.SwitchPawn[0].ColumnIndex = 6;
		BoardPawnSetup.SwitchPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[1].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[1].RowIndex = 4;
		BoardPawnSetup.SwitchPawn[1].ColumnIndex = 2;
		BoardPawnSetup.SwitchPawn[1].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.SwitchPawn[2].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[2].RowIndex = 3;
		BoardPawnSetup.SwitchPawn[2].ColumnIndex = 7;
		BoardPawnSetup.SwitchPawn[2].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.SwitchPawn[3].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[3].RowIndex = 2;
		BoardPawnSetup.SwitchPawn[3].ColumnIndex = 3;
		BoardPawnSetup.SwitchPawn[3].PawnSpawnYaw = 90.0f;
	
		// Deflector setup
		BoardPawnSetup.DeflectorPawn[0].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[0].RowIndex = 7;
		BoardPawnSetup.DeflectorPawn[0].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[0].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[1].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[1].RowIndex = 7;
		BoardPawnSetup.DeflectorPawn[1].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[2].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[2].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[2].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[2].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[3].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[3].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[3].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[3].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[4].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[4].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[4].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[4].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[5].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[5].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[5].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[5].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[6].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[6].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[6].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[6].PawnSpawnYaw = 0.0f;
	
	
		BoardPawnSetup.DeflectorPawn[7].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[7].RowIndex = 0;
		BoardPawnSetup.DeflectorPawn[7].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[7].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[8].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[8].RowIndex = 0;
		BoardPawnSetup.DeflectorPawn[8].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[8].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[9].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[9].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[9].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[9].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[10].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[10].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[10].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[10].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[11].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[11].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[11].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[11].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[12].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[12].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[12].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[12].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[13].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[13].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[13].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[13].PawnSpawnYaw = -90.0f;
	
		return BoardPawnSetup;
	}
			
	// Mercury Setup
	static FBoardPawnSetup Mercury()
	{
		FBoardPawnSetup BoardPawnSetup;
		// Laser setup
		BoardPawnSetup.LaserPawn[0].bIsTeamA = true;
		BoardPawnSetup.LaserPawn[0].RowIndex = 7;
		BoardPawnSetup.LaserPawn[0].ColumnIndex = 0;
		BoardPawnSetup.LaserPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.LaserPawn[1].bIsTeamA = false;
		BoardPawnSetup.LaserPawn[1].RowIndex = 0;
		BoardPawnSetup.LaserPawn[1].ColumnIndex = 9;
		BoardPawnSetup.LaserPawn[1].PawnSpawnYaw = -90.0f;
	
		// King setup
		BoardPawnSetup.KingPawn[0].bIsTeamA = true;
		BoardPawnSetup.KingPawn[0].RowIndex = 7;
		BoardPawnSetup.KingPawn[0].ColumnIndex = 5;
		BoardPawnSetup.KingPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.KingPawn[1].bIsTeamA = false;
		BoardPawnSetup.KingPawn[1].RowIndex = 0;
		BoardPawnSetup.KingPawn[1].ColumnIndex = 4;
		BoardPawnSetup.KingPawn[1].PawnSpawnYaw = 0.0f;
	
		// Defender setup
		BoardPawnSetup.DefenderPawn[0].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[0].RowIndex = 5;
		BoardPawnSetup.DefenderPawn[0].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[0].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[1].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[1].RowIndex = 5;
		BoardPawnSetup.DefenderPawn[1].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[1].PawnSpawnYaw = -180.0f;
	
		BoardPawnSetup.DefenderPawn[2].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[2].RowIndex = 1;
		BoardPawnSetup.DefenderPawn[2].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[2].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DefenderPawn[3].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[3].RowIndex = 2;
		BoardPawnSetup.DefenderPawn[3].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[3].PawnSpawnYaw = 0.0f;
	
		//Switch setup
		BoardPawnSetup.SwitchPawn[0].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[0].RowIndex = 0;
		BoardPawnSetup.SwitchPawn[0].ColumnIndex = 0;
		BoardPawnSetup.SwitchPawn[0].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.SwitchPawn[1].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[1].RowIndex = 5;
		BoardPawnSetup.SwitchPawn[1].ColumnIndex = 3;
		BoardPawnSetup.SwitchPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[2].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[2].RowIndex = 7;
		BoardPawnSetup.SwitchPawn[2].ColumnIndex = 9;
		BoardPawnSetup.SwitchPawn[2].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.SwitchPawn[3].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[3].RowIndex = 2;
		BoardPawnSetup.SwitchPawn[3].ColumnIndex = 6;
		BoardPawnSetup.SwitchPawn[3].PawnSpawnYaw = 90.0f;
	
		// Deflector setup
		BoardPawnSetup.DeflectorPawn[0].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[0].RowIndex = 7;
		BoardPawnSetup.DeflectorPawn[0].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[0].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[1].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[1].RowIndex = 7;
		BoardPawnSetup.DeflectorPawn[1].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[2].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[2].RowIndex = 6;
		BoardPawnSetup.DeflectorPawn[2].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[2].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[3].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[3].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[3].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[3].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[4].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[4].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[4].ColumnIndex = 1;
		BoardPawnSetup.DeflectorPawn[4].PawnSpawnYaw = 00.0f;
	
		BoardPawnSetup.DeflectorPawn[5].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[5].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[5].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[5].PawnSpawnYaw = 0.0f;
	
	
		BoardPawnSetup.DeflectorPawn[6].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[6].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[6].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[6].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[7].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[7].RowIndex = 0;
		BoardPawnSetup.DeflectorPawn[7].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[7].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[8].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[8].RowIndex = 0;
		BoardPawnSetup.DeflectorPawn[8].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[8].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[9].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[9].RowIndex = 1;
		BoardPawnSetup.DeflectorPawn[9].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[9].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[10].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[10].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[10].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[10].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[11].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[11].RowIndex = 4;
		BoardPawnSetup.DeflectorPawn[11].ColumnIndex = 8;
		BoardPawnSetup.DeflectorPawn[11].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[12].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[12].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[12].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[12].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[13].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[13].RowIndex = 3;
		BoardPawnSetup.DeflectorPawn[13].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[13].PawnSpawnYaw = 180.0f;
	
		return BoardPawnSetup;
	}
			
	// Sophie Setup
	static FBoardPawnSetup Sophie()
	{
		FBoardPawnSetup BoardPawnSetup;
		// Laser setup
		BoardPawnSetup.LaserPawn[0].bIsTeamA = true;
		BoardPawnSetup.LaserPawn[0].RowIndex = 7;
		BoardPawnSetup.LaserPawn[0].ColumnIndex = 0;
		BoardPawnSetup.LaserPawn[0].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.LaserPawn[1].bIsTeamA = false;
		BoardPawnSetup.LaserPawn[1].RowIndex = 0;
		BoardPawnSetup.LaserPawn[1].ColumnIndex = 9;
		BoardPawnSetup.LaserPawn[1].PawnSpawnYaw = -90.0f;
	
		// King setup
		BoardPawnSetup.KingPawn[0].bIsTeamA = true;
		BoardPawnSetup.KingPawn[0].RowIndex = 7;
		BoardPawnSetup.KingPawn[0].ColumnIndex = 4;
		BoardPawnSetup.KingPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.KingPawn[1].bIsTeamA = false;
		BoardPawnSetup.KingPawn[1].RowIndex = 0;
		BoardPawnSetup.KingPawn[1].ColumnIndex = 5;
		BoardPawnSetup.KingPawn[1].PawnSpawnYaw = 0.0f;
	
		// Defender setup
		BoardPawnSetup.DefenderPawn[0].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[0].RowIndex = 6;
		BoardPawnSetup.DefenderPawn[0].ColumnIndex = 3;
		BoardPawnSetup.DefenderPawn[0].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DefenderPawn[1].bIsTeamA = true;
		BoardPawnSetup.DefenderPawn[1].RowIndex = 6;
		BoardPawnSetup.DefenderPawn[1].ColumnIndex = 5;
		BoardPawnSetup.DefenderPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DefenderPawn[2].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[2].RowIndex = 1;
		BoardPawnSetup.DefenderPawn[2].ColumnIndex = 4;
		BoardPawnSetup.DefenderPawn[2].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DefenderPawn[3].bIsTeamA = false;
		BoardPawnSetup.DefenderPawn[3].RowIndex = 1;
		BoardPawnSetup.DefenderPawn[3].ColumnIndex = 6;
		BoardPawnSetup.DefenderPawn[3].PawnSpawnYaw = 0.0f;
	
		//Switch setup
		BoardPawnSetup.SwitchPawn[0].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[0].RowIndex = 4;
		BoardPawnSetup.SwitchPawn[0].ColumnIndex = 7;
		BoardPawnSetup.SwitchPawn[0].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.SwitchPawn[1].bIsTeamA = true;
		BoardPawnSetup.SwitchPawn[1].RowIndex = 2;
		BoardPawnSetup.SwitchPawn[1].ColumnIndex = 2;
		BoardPawnSetup.SwitchPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.SwitchPawn[2].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[2].RowIndex = 3;
		BoardPawnSetup.SwitchPawn[2].ColumnIndex = 2;
		BoardPawnSetup.SwitchPawn[2].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.SwitchPawn[3].bIsTeamA = false;
		BoardPawnSetup.SwitchPawn[3].RowIndex = 5;
		BoardPawnSetup.SwitchPawn[3].ColumnIndex = 7;
		BoardPawnSetup.SwitchPawn[3].PawnSpawnYaw = 90.0f;
	
		// Deflector setup
		BoardPawnSetup.DeflectorPawn[0].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[0].RowIndex = 1;
		BoardPawnSetup.DeflectorPawn[0].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[0].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[1].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[1].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[1].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[1].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[2].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[2].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[2].ColumnIndex = 0;
		BoardPawnSetup.DeflectorPawn[2].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[3].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[3].RowIndex = 0;
		BoardPawnSetup.DeflectorPawn[3].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[3].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[4].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[4].RowIndex = 7;
		BoardPawnSetup.DeflectorPawn[4].ColumnIndex = 6;
		BoardPawnSetup.DeflectorPawn[4].PawnSpawnYaw = 90.0f;
	
		BoardPawnSetup.DeflectorPawn[5].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[5].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[5].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[5].PawnSpawnYaw = 180.0f;
	
	
		BoardPawnSetup.DeflectorPawn[6].bIsTeamA = true;
		BoardPawnSetup.DeflectorPawn[6].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[6].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[6].PawnSpawnYaw = 90.0f;
	
	
		BoardPawnSetup.DeflectorPawn[7].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[7].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[7].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[7].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[8].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[8].RowIndex = 5;
		BoardPawnSetup.DeflectorPawn[8].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[8].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[9].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[9].RowIndex = 6;
		BoardPawnSetup.DeflectorPawn[9].ColumnIndex = 9;
		BoardPawnSetup.DeflectorPawn[9].PawnSpawnYaw = 180.0f;
	
		BoardPawnSetup.DeflectorPawn[10].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[10].RowIndex = 0;
		BoardPawnSetup.DeflectorPawn[10].ColumnIndex = 3;
		BoardPawnSetup.DeflectorPawn[10].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[11].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[11].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[11].ColumnIndex = 4;
		BoardPawnSetup.DeflectorPawn[11].PawnSpawnYaw = -90.0f;
	
		BoardPawnSetup.DeflectorPawn[12].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[12].RowIndex = 2;
		BoardPawnSetup.DeflectorPawn[12].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[12].PawnSpawnYaw = 0.0f;
	
		BoardPawnSetup.DeflectorPawn[13].bIsTeamA = false;
		BoardPawnSetup.DeflectorPawn[13].RowIndex = 7;
		BoardPawnSetup.DeflectorPawn[13].ColumnIndex = 5;
		BoardPawnSetup.DeflectorPawn[13].PawnSpawnYaw = -90.0f;
	
		return BoardPawnSetup;
	}
}