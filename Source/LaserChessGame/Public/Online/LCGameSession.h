// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "LCGameSession.generated.h"

/**
 * 
 */
UCLASS()
class LASERCHESSGAME_API ALCGameSession : public AGameSession
{
	GENERATED_BODY()
protected:
	ALCGameSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
