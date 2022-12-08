// Copyright Soumik Bhattacherjee All Rights Reserved.


#include "Player/LCCameraPawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/LCCameraPawnController.h"
#include "LaserChessGame.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ALCCameraPawn::ALCCameraPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PawnRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("PawnRootComp"));
	RootComponent = PawnRoot;

	PawnCameraArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("PawnCameraArmComp"));
	PawnCameraArm->SetupAttachment(PawnRoot);
	PawnCameraArm->bDoCollisionTest = false;
	PawnCameraArm->bUsePawnControlRotation = true;
	PawnCameraArm->bEnableCameraLag = true;
	PawnCameraArm->bEnableCameraRotationLag = true;
	PawnCameraArm->CameraLagSpeed = 5.0f;
	PawnCameraArm->CameraRotationLagSpeed = 10.0f;

	PawnMainCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("PawnMainCameraComp"));
	PawnMainCamera->SetupAttachment(PawnCameraArm, USpringArmComponent::SocketName);
	
	PrimaryActorTick.bCanEverTick = true;

	// Defaults
	MinCameraDist = 500.f;
	MaxCameraDist = 1500.f;
	CameraStep = 100.f;
	CameraMoveInOutSpeed = 10.0f;
	bCanRotateCamera = false;
	MouseSmoothness = 50.0f;
	MouseXAxisScaling = 6.0f;
	MouseYAxisScaling = 5.0f;
}

void ALCCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<ALCCameraPawnController>(GetController());
	TargetCameraDist = (MinCameraDist + MaxCameraDist) * 0.5f;
	if(PlayerControllerRef && GetNetMode() != NM_DedicatedServer)
	{
		PlayerControllerRef->ResetCamera();
		InitPlayerInput(PlayerControllerRef);
	}
}

void ALCCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Simple interpolation
	if (FMath::Abs(TargetCameraDist - PawnCameraArm->TargetArmLength) > KINDA_SMALL_NUMBER)
	{
		PawnCameraArm->TargetArmLength = FMath::FInterpTo(PawnCameraArm->TargetArmLength, TargetCameraDist, DeltaTime, CameraMoveInOutSpeed);
		if (FMath::Abs(TargetCameraDist - PawnCameraArm->TargetArmLength) <= SMALL_NUMBER)
		{
			PawnCameraArm->TargetArmLength = TargetCameraDist;
		}
	}
}

void ALCCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(CameraLookAction, ETriggerEvent::Triggered, this, &ALCCameraPawn::Input_CameraLook);
		EIC->BindAction(CameraMovingInAction, ETriggerEvent::Triggered, this, &ALCCameraPawn::Input_CameraIn);
		EIC->BindAction(CameraMovingOutAction, ETriggerEvent::Triggered, this, &ALCCameraPawn::Input_CameraOut);
		EIC->BindAction(ResetCameraAction, ETriggerEvent::Triggered, this, &ALCCameraPawn::Input_ResetCameraAction);
		
		EIC->BindAction(RightInputAction, ETriggerEvent::Started, this, &ALCCameraPawn::Input_RightAction);
		EIC->BindAction(RightInputAction, ETriggerEvent::Completed, this, &ALCCameraPawn::Input_RightAction);
		EIC->BindAction(LeftInputAction, ETriggerEvent::Started, this, &ALCCameraPawn::Input_LeftAction);
		EIC->BindAction(CancelInputAction, ETriggerEvent::Started, this, &ALCCameraPawn::Input_CancelAction);
	}
}

void ALCCameraPawn::Input_CameraLook(const FInputActionValue& InputActionValue)
{
	if (bCanRotateCamera)
	{
		FVector2D Value = InputActionValue.Get<FVector2D>();
		if(Value.IsZero())
			return;
		
		Value.Normalize();
		Value *= GetWorld()->GetDeltaSeconds();
		Value *= MouseSmoothness;	
		Value.X *= MouseXAxisScaling;
		Value.Y *= MouseYAxisScaling;

		AddControllerPitchInput(Value.Y);
		AddControllerYawInput(Value.X);
	}
}

void ALCCameraPawn::Input_CameraIn(const FInputActionValue& InputActionValue)
{
	if (TargetCameraDist > MinCameraDist)
	{
		TargetCameraDist -= CameraStep;
		TargetCameraDist = FMath::Max(TargetCameraDist, MinCameraDist);
	}
}

void ALCCameraPawn::Input_CameraOut(const FInputActionValue& InputActionValue)
{
	if (TargetCameraDist < MaxCameraDist)
	{
		TargetCameraDist += CameraStep;
		TargetCameraDist = FMath::Min(TargetCameraDist, MaxCameraDist);
	}
}

void ALCCameraPawn::Input_ResetCameraAction(const FInputActionValue& InputActionValue)
{
	PlayerControllerRef->ResetCamera();
	PlayerControllerRef->CenterMouseCursor();
}

void ALCCameraPawn::Input_RightAction(const FInputActionValue& InputActionValue)
{
	const bool bState = InputActionValue.Get<bool>();
	bCanRotateCamera = bState;
	PlayerControllerRef->bShowMouseCursor = !bState;
	PlayerControllerRef->CenterMouseCursor();
}

void ALCCameraPawn::Input_LeftAction(const FInputActionValue& InputActionValue)
{
}

void ALCCameraPawn::Input_CancelAction(const FInputActionValue& InputActionValue)
{
}

void ALCCameraPawn::InitPlayerInput(const APlayerController* InController)
{
	if (!PlayerInputMapping)
	{
		UE_LOG(LogLaserChess, Warning, TEXT("Trying to initialize player input with invalid InputMapping Data"));
		return;
	}

	if (!PlayerInputConfig)
	{
		UE_LOG(LogLaserChess, Warning, TEXT("Trying to initialize player input with invalid Input Config Data"));
		return;
	}

	if (!InController)
	{
		UE_LOG(LogLaserChess, Warning, TEXT("Trying to initialize player input with null player controller"));
		return;
	}

	if (!InController->GetLocalPlayer())
	{
		UE_LOG(LogLaserChess, Warning, TEXT("Trying to initialize player input with invalid Local Player"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EPSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(InController->GetLocalPlayer());

	if (!EPSubsystem)
	{
		UE_LOG(LogLaserChess, Warning, TEXT("Trying to initialize player input with invalid Input Subsystem"));
		return;
	}

	EPSubsystem->ClearAllMappings();
	EPSubsystem->AddMappingContext(PlayerInputMapping, InputPriority);
	EPSubsystem->AddPlayerMappableConfig(PlayerInputConfig);
}

