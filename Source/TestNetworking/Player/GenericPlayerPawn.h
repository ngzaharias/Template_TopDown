// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GenericPlayerPawn.generated.h"

UCLASS()
class TESTNETWORKING_API AGenericPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	AGenericPlayerPawn();

	FORCEINLINE class UCameraComponent* GetCamera() const { return m_Camera; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return m_CameraBoom; }
	FORCEINLINE class UDecalComponent* GetCursor() const { return m_Cursor; }
	FORCEINLINE class UPawnMovementComponent* GetMovementComponent() const override { return m_MovementComponent; }

	void Tick(float DeltaTime) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AdjustYaw(const float AxisValue);
	void AdjustZoom(const float AxisValue);
	void MoveHorizontal(const float AxisValue);
	void MoveVertical(const float AxisValue);
	void ToggleYawAdjustments();

	/* CLIENT */

	/* SERVER */


protected:
	void BeginPlay() override;

public:
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_Camera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* m_CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cursor, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* m_Cursor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UPawnMovementComponent* m_MovementComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_AdjustYawSpeed = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_AdjustZoomSpeed = 1.f;

	bool m_bIsCameraRotateEnabled = false;

	/* CLIENT */

	/* SERVER */
};
