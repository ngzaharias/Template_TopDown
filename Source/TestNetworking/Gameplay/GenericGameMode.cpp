// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestNetworking.h"
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

	FActorSpawnParameters CharacterManagerParams;
	CharacterManagerParams.ObjectFlags |= RF_Transient;
	CharacterManager = NewObject<ACharacterManager>();
}

void AGenericGameMode::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl& UniqueId, FString & ErrorMessage)
{
	AGameModeBase::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AGenericGameMode::PostLogin(APlayerController * NewPlayer)
{
	AGameModeBase::PostLogin(NewPlayer);

	ACharacter* Character = NULL;
	FActorSpawnParameters SpawnParameters;
	CharacterManager->CreateCharacter(CharacterClass, SpawnParameters, Character, NewPlayer);
}

