// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Player/LCPawnCameraManager.h"

ALCPawnCameraManager::ALCPawnCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ViewPitchMin = -85.0f;
	ViewPitchMax = -15.0f;
}
