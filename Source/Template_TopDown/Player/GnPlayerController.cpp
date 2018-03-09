// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Template_TopDown.h"
#include "GnPlayerController.h"

#include "Characters/CharacterManager.h"
#include "Characters/GnCharacter.h"
#include "Game/GnGameMode.h"
#include "Player/GnPlayerPawn.h"

#include <AI/Navigation/NavigationSystem.h>
#include <Runtime/Engine/Classes/Components/DecalComponent.h>
#include <Runtime/Engine/Classes/GameFramework/Actor.h>


AGnPlayerController::AGnPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

AGnPlayerPawn* AGnPlayerController::GetGnPawn() const
{
	return Cast<AGnPlayerPawn>(GetPawn());
}

void AGnPlayerController::BeginPlay()
{
}

void AGnPlayerController::BeginPlayingState()
{
}

void AGnPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AGnPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectPrimary",		IE_Pressed, this, &AGnPlayerController::SelectPrimary);
	InputComponent->BindAction("SelectSecondary",	IE_Pressed, this, &AGnPlayerController::SelectSecondary);
	InputComponent->BindAction("SelectTertiary",	IE_Pressed, this, &AGnPlayerController::SelectTertiary);
	InputComponent->BindAction("SelectTertiary",	IE_Released, this, &AGnPlayerController::SelectTertiary);

	InputComponent->BindAxis("CameraHorizontal",	this, &AGnPlayerController::CameraHorizontal);
	InputComponent->BindAxis("CameraVertical",		this, &AGnPlayerController::CameraVertical);
	InputComponent->BindAxis("CameraYaw",			this, &AGnPlayerController::CameraYaw);
	InputComponent->BindAxis("CameraZoom",			this, &AGnPlayerController::CameraZoom);
}

void AGnPlayerController::CameraHorizontal(const float AxisValue)
{
	AGnPlayerPawn* const playerPawn = GetGnPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->MoveHorizontal(AxisValue);
	}
}

void AGnPlayerController::CameraVertical(const float AxisValue)
{
	AGnPlayerPawn* const playerPawn = GetGnPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->MoveVertical(AxisValue);
	}
}

void AGnPlayerController::CameraYaw(const float AxisValue)
{
	AGnPlayerPawn* const playerPawn = GetGnPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->AdjustYaw(AxisValue);
	}
}

void AGnPlayerController::CameraZoom(const float AxisValue)
{
	AGnPlayerPawn* const playerPawn = GetGnPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->AdjustZoom(AxisValue);
	}
}

void AGnPlayerController::SelectPrimary()
{
	FHitResult hit;
	GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if (hit.bBlockingHit)
	{
		Server_SelectPrimary(hit.Location);
	}
}

void AGnPlayerController::SelectSecondary()
{
}

void AGnPlayerController::SelectTertiary()
{
	AGnPlayerPawn* const playerPawn = GetGnPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->ToggleYawAdjustments();
	}
}

bool AGnPlayerController::Client_BeginPlayingState_Validate()
{
	return true;
}

void AGnPlayerController::Client_BeginPlayingState_Implementation()
{
	const AGnPlayerPawn* const playerPawn = GetGnPawn();
	UDecalComponent* const cursor = playerPawn->GetCursor();
	cursor->SetVisibility(true);
}

bool AGnPlayerController::Server_SelectPrimary_Validate(FVector Location)
{
	return true;
}

void AGnPlayerController::Server_SelectPrimary_Implementation(FVector Location)
{
	const AGnGameMode* const gameMode = (AGnGameMode*)GetWorld()->GetAuthGameMode();
	ACharacterManager* const characterManager = gameMode->GetCharacterManager();
	ACharacter* const playerCharacter = characterManager->GetCharacterFromPlayer(this);

	checkf(playerCharacter, TEXT("Character is null! Player doesn't have a character assigned to them."));
	if (playerCharacter == nullptr)
		return;

	AController* controller = playerCharacter->GetController();
	UNavigationSystem::SimpleMoveToLocation(controller, Location);
}