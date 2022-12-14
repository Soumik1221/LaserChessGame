// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Declare Laser Chess Game Log
DECLARE_LOG_CATEGORY_EXTERN(LogLaserChess, Log, All);

#define LC_BOARD_ROWS 8
#define LC_BOARD_COLUMNS 10

#define LC_BOARD_PAWN_COUNT_LASER 2
#define LC_BOARD_PAWN_COUNT_KING 2
#define LC_BOARD_PAWN_COUNT_SWITCH 4
#define LC_BOARD_PAWN_COUNT_DEFENDER 4
#define LC_BOARD_PAWN_COUNT_DEFLECTOR 14

// Do not modify change above
#define LC_BOARD_PAWNS	LC_BOARD_PAWN_COUNT_LASER + \
						LC_BOARD_PAWN_COUNT_KING +\
						LC_BOARD_PAWN_COUNT_SWITCH +\
						LC_BOARD_PAWN_COUNT_DEFENDER +\
						LC_BOARD_PAWN_COUNT_DEFLECTOR\

namespace LCHelperFunc
{
	static bool GetRowColumnFromIndex(int32 InIndex, int32& RowIndex, int32& ColumnIndex)
	{
		if(InIndex < LC_BOARD_ROWS * LC_BOARD_COLUMNS)
		{
			RowIndex = InIndex / LC_BOARD_ROWS;
			ColumnIndex = InIndex % LC_BOARD_ROWS;
			return true;
		}
		return false;
	}

	static bool GetIndexFromRowColumn(int32 RowIndex, int32 ColumnIndex, int32& InIndex)
	{
		if(RowIndex < LC_BOARD_ROWS && ColumnIndex < LC_BOARD_COLUMNS)
		{
			InIndex =  RowIndex * LC_BOARD_COLUMNS + ColumnIndex;
			return true;
		}
		return false;
	}
	
}
