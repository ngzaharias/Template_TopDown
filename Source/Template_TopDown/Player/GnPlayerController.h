// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "GnPlayerController.generated.h"

UCLASS()
class AGnPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGnPlayerController();

protected:
	class AGnPlayerPawn* GetGnPawn() const;

	void BeginPlay() override;
	void BeginPlayingState() override;
	void PlayerTick(float DeltaTime) override;
	void SetupInputComponent() override;

	void CameraHorizontal(const float AxisValue);
	void CameraVertical(const float AxisValue);
	void CameraYaw(const float AxisValue);
	void CameraZoom(const float AxisValue);
	void SelectPrimary();
	void SelectSecondary();
	void SelectTertiary();

	/* CLIENT */
	UFUNCTION(Client, Reliable, WithValidation)
		void Client_BeginPlayingState();

	/* SERVER */
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SelectPrimary(FVector Location);

protected:
	
};


