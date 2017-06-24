// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestNetworking.h"
#include "GenericPlayerController.h"

#include "Gameplay/GenericGameMode.h"
#include "Gameplay/Characters/CharacterManager.h"
#include "Gameplay/Characters/GenericCharacter.h"
#include "Player/GenericPlayerPawn.h"

#include <AI/Navigation/NavigationSystem.h>
#include <Runtime/Engine/Classes/Components/DecalComponent.h>
#include <Runtime/Engine/Classes/GameFramework/Actor.h>


AGenericPlayerController::AGenericPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

AGenericPlayerPawn* AGenericPlayerController::GetGenericPawn() const
{
	return Cast<AGenericPlayerPawn>(GetPawn());
}

void AGenericPlayerController::BeginPlay()
{
}

void AGenericPlayerController::BeginPlayingState()
{
}

void AGenericPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AGenericPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectPrimary",		IE_Pressed, this, &AGenericPlayerController::SelectPrimary);
	InputComponent->BindAction("SelectSecondary",	IE_Pressed, this, &AGenericPlayerController::SelectSecondary);
	InputComponent->BindAction("SelectTertiary",	IE_Pressed, this, &AGenericPlayerController::SelectTertiary);
	InputComponent->BindAction("SelectTertiary",	IE_Released, this, &AGenericPlayerController::SelectTertiary);

	InputComponent->BindAxis("CameraHorizontal",	this, &AGenericPlayerController::CameraHorizontal);
	InputComponent->BindAxis("CameraVertical",		this, &AGenericPlayerController::CameraVertical);
	InputComponent->BindAxis("CameraYaw",			this, &AGenericPlayerController::CameraYaw);
	InputComponent->BindAxis("CameraZoom",			this, &AGenericPlayerController::CameraZoom);
}

void AGenericPlayerController::CameraHorizontal(const float AxisValue)
{
	AGenericPlayerPawn* const playerPawn = GetGenericPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->MoveHorizontal(AxisValue);
	}
}

void AGenericPlayerController::CameraVertical(const float AxisValue)
{
	AGenericPlayerPawn* const playerPawn = GetGenericPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->MoveVertical(AxisValue);
	}
}

void AGenericPlayerController::CameraYaw(const float AxisValue)
{
	AGenericPlayerPawn* const playerPawn = GetGenericPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->AdjustYaw(AxisValue);
	}
}

void AGenericPlayerController::CameraZoom(const float AxisValue)
{
	AGenericPlayerPawn* const playerPawn = GetGenericPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->AdjustZoom(AxisValue);
	}
}

void AGenericPlayerController::SelectPrimary()
{
	FHitResult hit;
	GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if (hit.bBlockingHit)
	{
		Server_SelectPrimary(hit.Location);
	}
}

void AGenericPlayerController::SelectSecondary()
{
}

void AGenericPlayerController::SelectTertiary()
{
	AGenericPlayerPawn* const playerPawn = GetGenericPawn();
	if (playerPawn != nullptr)
	{
		playerPawn->ToggleYawAdjustments();
	}
}

bool AGenericPlayerController::Client_BeginPlayingState_Validate()
{
	return true;
}

void AGenericPlayerController::Client_BeginPlayingState_Implementation()
{
	const AGenericPlayerPawn* const playerPawn = GetGenericPawn();
	UDecalComponent* const cursor = playerPawn->GetCursor();
	cursor->SetVisibility(true);
}

bool AGenericPlayerController::Server_SelectPrimary_Validate(FVector Location)
{
	return true;
}

void AGenericPlayerController::Server_SelectPrimary_Implementation(FVector Location)
{
	const AGenericGameMode* const gameMode = (AGenericGameMode*)GetWorld()->GetAuthGameMode();
	ACharacterManager* const characterManager = gameMode->GetCharacterManager();
	ACharacter* const playerCharacter = characterManager->GetCharacterFromPlayer(this);

	checkf(playerCharacter, TEXT("Character is null! Player doesn't have a character assigned to them."));
	if (playerCharacter == nullptr)
		return;

	AController* controller = playerCharacter->GetController();
	UNavigationSystem::SimpleMoveToLocation(controller, Location);
}