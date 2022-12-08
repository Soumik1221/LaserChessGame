// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LCGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LASERCHESSGAME_API ALCGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	ALCGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
