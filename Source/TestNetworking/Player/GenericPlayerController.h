// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "GenericPlayerController.generated.h"

UCLASS()
class AGenericPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGenericPlayerController();

protected:
	void BeginPlay() override;
	void BeginPlayingState() override;
	void PlayerTick(float DeltaTime) override;
	void SetupInputComponent() override;

	/* CLIENT */

	/* SERVER */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveToMouseCursor();

protected:
	/* CLIENT */

	/* SERVER */
};


