// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "LaserChessGameTypes.generated.h"

/** Pawn player team */
UENUM(BlueprintType)
enum class EPawnTeam : uint8
{
	EPT_TeamA UMETA(DisplayName = "Pawn Team A"),
	EPT_TeamB UMETA(DisplayName = "Pawn Team B")
};

/** Different laser chess board tiles */
UENUM(BlueprintType)
enum class ETileType : uint8
{
	ETT_TeamA   UMETA(DisplayName = "Team A Tile"),
	ETT_TeamB   UMETA(DisplayName = "Team B Tile"),
	ETT_Both    UMETA(DisplayName = "Team Both Tile"),
	ETT_Laser   UMETA(DisplayName = "Laser Pawn Tile")
};

/** Pawn type */
UENUM(BlueprintType)
enum class EPawnType : uint8
{
	EPT_Laser		UMETA(DisplayName = "Laser"),
	EPT_King		UMETA(DisplayName = "King"),
	EPT_Switch		UMETA(DisplayName = "Switch"),
	EPT_Defender	UMETA(DisplayName = "Defender"),
	EPT_Deflector	UMETA(DisplayName = "Deflector")
};

/** Board setup  */
UENUM(BlueprintType)
enum class EBoardSetup :uint8
{
	EBS_ACE			UMETA(DisplayName = "Ace"),
	EBS_CURIOSITY	UMETA(DisplayName = "Curiosity"),
	EBS_GRAIL		UMETA(DisplayName = "Grail"),
	EBS_MERCURY		UMETA(DisplayName = "Mercury"),
	EBS_SOPHIE		UMETA(DisplayName = "Sophie")
};
