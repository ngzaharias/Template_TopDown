// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Template_TopDown.h"
#include "GnGameMode.h"
#include "GnGameState.h"
#include "Characters/CharacterManager.h"
#include "Characters/GnCharacter.h"
#include "Player/GnPlayerController.h"
#include "Player/GnPlayerPawn.h"
#include "Player/GnPlayerState.h"

AGnGameMode::AGnGameMode()
{
	// inherited
	DefaultPawnClass = AGnPlayerPawn::StaticClass();
	PlayerControllerClass = AGnPlayerController::StaticClass();
	GameStateClass = AGnGameState::StaticClass();
	PlayerStateClass = AGnPlayerState::StaticClass();

	// custom
	CharacterClass = AGnCharacter::StaticClass();
}

void AGnGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	FActorSpawnParameters CharacterManagerParams;
	CharacterManagerParams.ObjectFlags |= RF_Transient;
	m_CharacterManager = NewObject<ACharacterManager>();
	m_CharacterManager->Init(GetWorld());
}

void AGnGameMode::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl& UniqueId, FString & ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AGnGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	FActorSpawnParameters SpawnParameters;
	AGnCharacter* Character = m_CharacterManager->CreateCharacter(CharacterClass, SpawnParameters);
	AGnPlayerController* Controller = Cast<AGnPlayerController>(NewPlayer);
	if (Character && Controller)
	{
		m_CharacterManager->RegisterCharacter(Character);
		m_CharacterManager->RegisterPlayer(Controller);
		m_CharacterManager->AssignCharacterToPlayer(Controller, Character);
		Character->SetActorLocation(Controller->GetSpawnLocation());
	}
}

