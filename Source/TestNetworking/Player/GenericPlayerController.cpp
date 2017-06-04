// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestNetworking.h"
#include "GenericPlayerController.h"

#include "Gameplay/Characters/GenericCharacter.h"
#include "Player/GenericPlayerPawn.h"

#include <AI/Navigation/NavigationSystem.h>
#include <Runtime/Engine/Classes/Components/DecalComponent.h>
#include <Runtime/Engine/Classes/GameFramework/Actor.h>


AGenericPlayerController::AGenericPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AGenericPlayerController::BeginPlay()
{
}

void AGenericPlayerController::BeginPlayingState()
{
	if (IsLocalPlayerController() == false)
		return;

	APawn* const pawn = GetPawn();
	AGenericPlayerPawn* const playerPawn = Cast<AGenericPlayerPawn>(pawn);
	UDecalComponent* const cursor = playerPawn->GetCursor();
	cursor->SetVisibility(true);
}

void AGenericPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AGenericPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AGenericPlayerController::Server_MoveToMouseCursor);
}

bool AGenericPlayerController::Server_MoveToMouseCursor_Validate()
{
	return true;
}

void AGenericPlayerController::Server_MoveToMouseCursor_Implementation()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
	}
}