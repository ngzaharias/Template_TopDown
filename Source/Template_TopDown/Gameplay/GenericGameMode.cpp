// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Template_TopDown.h"
#include "GenericGameMode.h"
#include "GenericGameState.h"
#include "Gameplay/Characters/CharacterManager.h"
#include "Gameplay/Characters/GenericCharacter.h"
#include "Player/GenericPlayerController.h"
#include "Player/GenericPlayerPawn.h"
#include "Player/GenericPlayerState.h"

AGenericGameMode::AGenericGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/B_GenericPlayerPawn"));
	static ConstructorHelpers::FClassFinder<ACharacter> CharacterBPClass(TEXT("/Game/Characters/B_GenericCharacter"));

	CharacterClass = CharacterBPClass.Class;
	DefaultPawnClass = PlayerPawnBPClass.Class;
	PlayerControllerClass = AGenericPlayerController::StaticClass();
	GameStateClass = AGenericGameState::StaticClass();
	PlayerStateClass = AGenericPlayerState::StaticClass();
}

void AGenericGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	FActorSpawnParameters CharacterManagerParams;
	CharacterManagerParams.ObjectFlags |= RF_Transient;
	m_CharacterManager = NewObject<ACharacterManager>();
	m_CharacterManager->Init(GetWorld());
}

void AGenericGameMode::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl& UniqueId, FString & ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AGenericGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	FActorSpawnParameters SpawnParameters;
	ACharacter* Character = m_CharacterManager->CreateCharacter(CharacterClass, SpawnParameters);
	if (Character != nullptr)
	{
		m_CharacterManager->RegisterCharacter(Character);
		m_CharacterManager->RegisterPlayer(NewPlayer);
		m_CharacterManager->AssignCharacterToPlayer(NewPlayer, Character);
		Character->SetActorLocation(NewPlayer->GetSpawnLocation());
	}
}

