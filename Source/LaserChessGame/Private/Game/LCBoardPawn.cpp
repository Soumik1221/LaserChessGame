// Copyright Soumik Bhattacherjee All Rights Reserved.

#include "Game/LCBoardPawn.h"
#include "Game/LaserChessGameTypes.h"
#include "Game/LCBoardTile.h"
#include "Online/LCGameState.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LaserChessGame.h"
#include "Net/UnrealNetwork.h"

ALCBoardPawn::ALCBoardPawn(const FObjectInitializer& ObjectInitializer)
{
	PawnRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("PawnRootComp"));
	RootComponent = PawnRoot;

	PawnMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PawnMeshComp"));
	PawnMesh->SetupAttachment(PawnRoot);
	
	PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;
	bReplicates = true;
	PawnTeam = EPawnTeam::EPT_TeamA;
	PawnType = EPawnType::EPT_Laser;
}

void ALCBoardPawn::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
	GameStateOwner = GetWorld()->GetGameState<ALCGameState>();
}

void ALCBoardPawn::OnRep_PawnType(EPawnType OldType)
{
	if(PawnType != OldType)
	{
		OnPawnTypeChanged(PawnType);
	}
}

void ALCBoardPawn::OnRep_PawnTeam(EPawnTeam OldTeam)
{
	if(PawnTeam != OldTeam)
	{
		OnPawnTeamChanged(PawnTeam);
	}
}

void ALCBoardPawn::InitServerBoardPawn(class ALCBoardTile* InTile, int32 InIndex, bool bIsTeamA, EPawnType InType)
{
	PawnTeam = bIsTeamA ? EPawnTeam::EPT_TeamA : EPawnTeam::EPT_TeamB;
	PawnType = InType;
	PawnIndex = InIndex;
	SetTile(InTile);

	// Set location to that of it's tile immediately
	if(TileRef)
		SetActorLocation(TileRef->GetActorLocation());
	
	// For standalone and listen server update immediately
	if(GetNetMode() == NM_Standalone || GetNetMode() == NM_ListenServer)
	{
		OnPawnTypeChanged(PawnType);
		OnPawnTeamChanged(PawnTeam);
	}
}

void ALCBoardPawn::UpdatePawnsVisualsForClients()
{
	if(PawnType == EPawnType::EPT_Laser)
		OnPawnTypeChanged(PawnType);
	
	if(PawnTeam == EPawnTeam::EPT_TeamA)
		OnPawnTeamChanged(PawnTeam);
}

void ALCBoardPawn::SetTile(ALCBoardTile* InTile)
{
	if (InTile && TileRef != InTile)
	{
		// Invalidate pawn for previously occupied tile
		if(TileRef)
			TileRef->SetPawn(nullptr);
		// Set new tile
		TileRef = InTile;
		TileRef->SetPawn(this);

		UE_LOG(LogLaserChess, Log, TEXT("Pawn %s, tile reference changed to: %s"), *GetName(), *TileRef->GetName());
	}
}

void ALCBoardPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALCBoardPawn, PawnTeam);
	DOREPLIFETIME(ALCBoardPawn, PawnType);
	DOREPLIFETIME(ALCBoardPawn, PawnIndex);
	DOREPLIFETIME(ALCBoardPawn, TileRef);
}
