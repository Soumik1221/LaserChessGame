// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Player/LCCameraPawnController.h"

#include "LaserChessGame.h"
#include "Net/UnrealNetwork.h"

#include "Player/LCPawnCameraManager.h"
#include "Player/LCCameraPawn.h"
#include "Online/LCGameState.h"

#include "Game/LaserChessGameTypes.h"
#include "Game/LCBoardTile.h"
#include "Game/LCBoardPawn.h"
#include "Kismet/GameplayStatics.h"

ALCCameraPawnController::ALCCameraPawnController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ALCPawnCameraManager::StaticClass();
	bShowMouseCursor = true;
	PawnTileRegistrationUpdate = 0.5f;
}

void ALCCameraPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledCameraPawnRef = Cast<ALCCameraPawn>(InPawn);
}

void ALCCameraPawnController::BeginPlay()
{
	Super::BeginPlay();
	LaserChessGameStateRef = GetWorld()->GetGameState<ALCGameState>();
	
	if(LaserChessGameStateRef)
		OnPlayerControllerReady();
}

void ALCCameraPawnController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Failsafe If LaserChessGameStateRef could not be set on begin play try to set it every frame until we succeed.
	if(!LaserChessGameStateRef)
	{
		UE_LOG(LogLaserChess, Log, TEXT("Laser Chess Player Controller: Trying to set Game State Ref from Tick."));
		LaserChessGameStateRef = GetWorld()->GetGameState<ALCGameState>();
		
		if(LaserChessGameStateRef)
			OnPlayerControllerReady();
	}
	
}

void ALCCameraPawnController::OnPlayerControllerReady()
{
	UE_LOG(LogLaserChess, Log, TEXT("Laser Chess Player Controller: Player Controller is ready."));
	const bool bIsFromListenServer = GetNetMode() == NM_ListenServer && GetLocalRole() == ROLE_Authority;
	const bool bIsFromDedicatedServerClient = GetNetMode() == NM_Client && GetRemoteRole() == ROLE_Authority;
	if (!bHasValidGameStateOnClient && (bIsFromListenServer || bIsFromDedicatedServerClient))
	{
		bHasValidGameStateOnClient = true;
		SyncToClientGameState(bHasValidGameStateOnClient);
		
		// As now game state is valid check for pawn and tiles
		GetWorldTimerManager().SetTimer(TimeHandle_ClientGameStatePawnTileRegister, this,
			&ALCCameraPawnController::ClientGameStatePawnTileRegister, PawnTileRegistrationUpdate, true);
	}
}

void ALCCameraPawnController::ResetCamera()
{
	const bool bIsTeamA = PawnTeam == EPawnTeam::EPT_TeamA;
	const float YawRot = bIsTeamA ? 0.0f : 180.0f;
	SetControlRotation(FRotator(-50.0f, YawRot, 0.0f));

	UE_LOG(LogLaserChess, Warning, TEXT("Camera Pawn Team: %s"), bIsTeamA ? *FString("TeamA") : *FString("TeamB"));
}

void ALCCameraPawnController::CenterMouseCursor()
{
	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);

	SizeX /= 2;
	SizeY /= 2;

	SetMouseLocation(SizeX, SizeY);
}

bool ALCCameraPawnController::IsPlayerReadyForInitGame() const
{
	return bHasValidGameStateOnClient;
}

EPawnTeam ALCCameraPawnController::GetPlayerChosenTeam() const
{
	return EPawnTeam::EPT_TeamA; // TODO: For now first player to join will always be Player Team A.
}

void ALCCameraPawnController::SetServerPawnTeam(EPawnTeam NewTeam)
{
	if(GetLocalRole() == ROLE_Authority)
	{
		PawnTeam = NewTeam;

		// Set team info inside client
		SetClientPawnTeam(PawnTeam);
	}
	else
	{
		UE_LOG(LogLaserChess, Warning, TEXT("SetServerPawnTeam is not called from autharity."));
	}
}

void ALCCameraPawnController::ClientGameStatePawnTileRegister()
{
	TArray<AActor*> BoardTiles, BoardPawns;
	UGameplayStatics::GetAllActorsOfClass(this, ALCBoardTile::StaticClass(), BoardTiles);
	UGameplayStatics::GetAllActorsOfClass(this, ALCBoardPawn::StaticClass(), BoardPawns);
	
	if(BoardTiles.Num() == LC_BOARD_ROWS * LC_BOARD_COLUMNS || BoardPawns.Num() == LC_BOARD_PAWNS)
	{
		GetWorldTimerManager().ClearTimer(TimeHandle_ClientGameStatePawnTileRegister);
		LaserChessGameStateRef->RegisterTilesAndPawnsClient(BoardTiles, BoardPawns);
	}
}

void ALCCameraPawnController::SyncToClientGameState_Implementation(bool bState)
{
	UE_LOG(LogLaserChess, Warning, TEXT("Laser Chess Player Controller: [%s] SyncToClientGameState State Changed: %d"), *GetName(), bState);
	bHasValidGameStateOnClient = bState;
}

void ALCCameraPawnController::SetClientPawnTeam_Implementation(EPawnTeam NewTeam)
{
	PawnTeam = NewTeam;
	ResetCamera();
	bShowMouseCursor = true;
	CenterMouseCursor();
}

void ALCCameraPawnController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALCCameraPawnController, PawnTeam)
	DOREPLIFETIME(ALCCameraPawnController, ControlledCameraPawnRef)
}
