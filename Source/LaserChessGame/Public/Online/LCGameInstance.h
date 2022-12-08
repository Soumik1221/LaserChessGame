// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LASERCHESSGAME_API ULCGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	ULCGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
