// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Player/LCCameraPawnController.h"

#include "LaserChessGame.h"
#include "Net/UnrealNetwork.h"

#include "Player/LCPawnCameraManager.h"
#include "Player/LCCameraPawn.h"
#include "Online/LCGameState.h"

#include "Game/LaserChessGameTypes.h"

ALCCameraPawnController::ALCCameraPawnController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ALCPawnCameraManager::StaticClass();
	bShowMouseCursor = true;
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

	// Failsafe If LaserChessGameStateRef could not be set on begin play try to set it every frame
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
		// @TODO: Inform Game state to register spawned tiles and pawns
		
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

void ALCCameraPawnController::SyncToClientGameState_Implementation(bool bState)
{
	UE_LOG(LogLaserChess, Warning, TEXT("Laser Chess Player Controller: [%s] SyncToClientGameState State Changed: %d"), *GetName(), bState);
	bHasValidGameStateOnClient = bState;
}

void ALCCameraPawnController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALCCameraPawnController, PawnTeam)
	DOREPLIFETIME(ALCCameraPawnController, ControlledCameraPawnRef)
}
