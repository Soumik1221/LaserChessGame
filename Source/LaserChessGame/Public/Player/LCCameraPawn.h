// Copyright Soumik Bhattacherjee All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LCCameraPawn.generated.h"

class UInputMappingContext;
class UPlayerMappableInputConfig;
class UInputAction;

UCLASS()
class LASERCHESSGAME_API ALCCameraPawn : public APawn
{
	GENERATED_BODY()

private:
	/** Pawn scene root component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USceneComponent> PawnRoot;
	
	/** Spring arm component where the main camera will be attached to */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USpringArmComponent> PawnCameraArm;

	/** Main pawn camera c */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Scene, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UCameraComponent> PawnMainCamera;

protected:

	/** Minimum camera distance from chess board */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Camera Config", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MinCameraDist;

	/** Maximum camera distance from chess board */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Camera Config", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MaxCameraDist;

	/** How much camera move in and out. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Camera Config", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float CameraStep;

	/** How fast Camera should interp to its current target distance */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Camera Config", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float CameraMoveInOutSpeed;

	/** Mouse smoothness for both X and Y axis */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Camera Config", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MouseSmoothness;

	/** Mouse smoothness scaling for X axis */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Camera Config", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MouseXAxisScaling;

	/** Mouse smoothness scaling for Y axis */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Camera Config", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MouseYAxisScaling;


	/** Player input mapping context. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerInputMapping;

	/** Player input mappable config. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UPlayerMappableInputConfig> PlayerInputConfig;

	/** Input action for camera look up/down and left/right */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Camera Actions")
	TObjectPtr<UInputAction> CameraLookAction;

	/**  Input action for camera moving In */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Camera Actions")
	TObjectPtr<UInputAction> CameraMovingInAction;

	/**  Input action for camera moving Out */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Camera Actions")
	TObjectPtr<UInputAction> CameraMovingOutAction;

	/**  Input action for resetting player camera rotation. */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Camera Actions")
	TObjectPtr<UInputAction> ResetCameraAction;
	
	/**  Input action for right mouse click or similar */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> RightInputAction;

	/**  Input action for left mouse click or similar */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> LeftInputAction;

	/**  Input action for cancel current pawn's move. */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> CancelInputAction;

	
private:
	/** Player controller reference */
	UPROPERTY()
	TObjectPtr<class ALCCameraPawnController> PlayerControllerRef;

	/** If true player can rotate camera */
	uint8 bCanRotateCamera : 1;

	/** Current target distance. */
	float TargetCameraDist;

protected:
	ALCCameraPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void Input_CameraLook(const struct FInputActionValue& InputActionValue);
	void Input_CameraIn(const struct FInputActionValue& InputActionValue);
	void Input_CameraOut(const struct FInputActionValue& InputActionValue);
	void Input_ResetCameraAction(const struct FInputActionValue& InputActionValue);
	
	void Input_RightAction(const struct FInputActionValue& InputActionValue);
	void Input_LeftAction(const struct FInputActionValue& InputActionValue);
	void Input_CancelAction(const struct FInputActionValue& InputActionValue);

public:
	/** Init player input system from given controller */
	void InitPlayerInput(const APlayerController* InController);

};
