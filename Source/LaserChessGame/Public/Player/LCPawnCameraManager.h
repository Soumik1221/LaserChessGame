// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "LCPawnCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class LASERCHESSGAME_API ALCPawnCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:
	ALCPawnCameraManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
