// Fill out your copyright notice in the Description page of Project Settings.

#include "Template_TopDown.h"
#include "CharacterManager.h"
#include "GenericCharacter.h"


ACharacterManager::ACharacterManager()
{
}

UWorld* ACharacterManager::GetWorld() const 
{ 
	checkf(m_World != nullptr, TEXT("Trying to use CharacterManager with an null m_World."));
	return m_World; 
}

void ACharacterManager::Init(class UWorld* World)
{
	checkf(World != nullptr, TEXT("Trying to Init CharacterManager with a null UWorld."));
	m_World = World;
}

void ACharacterManager::Reset()
{
	m_CharacterToPlayerMap.Empty(0);
	m_PlayerToCharacterMap.Empty(0);
}

bool ACharacterManager::IsCharacterAssigned(class ACharacter* Character, class APlayerController* Player /*= nullptr*/)
{ 
	if (Player != nullptr)
		return m_CharacterToPlayerMap[Character] == Player;
	return m_CharacterToPlayerMap[Character] != nullptr; 
}

bool ACharacterManager::IsPlayerAssigned(class APlayerController* Player, class ACharacter* Character /*= nullptr*/)
{
	if (Character != nullptr)
		return m_PlayerToCharacterMap[Player] == Character;
	return m_PlayerToCharacterMap[Player] != nullptr;
}

bool ACharacterManager::AssignCharacterToPlayer(class APlayerController* Player, class ACharacter* NewCharacter /*= nullptr*/)
{
	if (NewCharacter != nullptr && IsCharacterAssigned(NewCharacter))
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Trying to assign a an already assigned character to another player."));
		return false;
	}

	// take the current character and clear its player
	ACharacter* const CurrentCharacter = m_PlayerToCharacterMap[Player];
	if (CurrentCharacter != nullptr)
	{
		m_CharacterToPlayerMap[CurrentCharacter] = nullptr;
	}
	// assign the new character to the player
	if (NewCharacter != nullptr)
	{
		m_CharacterToPlayerMap[NewCharacter] = Player;
	}

	m_PlayerToCharacterMap[Player] = NewCharacter;
	return true;
}

bool ACharacterManager::AssignPlayerToCharacter(class ACharacter* Character, class APlayerController* NewPlayer /*= nullptr*/)
{
	if (NewPlayer != nullptr && IsPlayerAssigned(NewPlayer))
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Trying to assign a an already assigned player to another character."));
		return false;
	}

	// take the current player and clear its character
	APlayerController* const CurrentPlayer = m_CharacterToPlayerMap[Character];
	if (CurrentPlayer != nullptr)
	{
		m_PlayerToCharacterMap[CurrentPlayer] = nullptr;
	}
	// assign the new player to the character
	if (NewPlayer != nullptr)
	{
		m_PlayerToCharacterMap[NewPlayer] = Character;
	}

	m_CharacterToPlayerMap[Character] = NewPlayer;
	return true;
}

ACharacter* ACharacterManager::CreateCharacter(UClass* Class, const FActorSpawnParameters& SpawnParameters)
{
	ACharacter* Character = GetWorld()->SpawnActor<ACharacter>(Class, SpawnParameters);
	if (Character == nullptr)
	{
		UE_LOG(LogCharacterManager, Error, TEXT("Couldn't create character."));
		return nullptr;
	}

	Character->SpawnDefaultController();
	return Character;
}

bool ACharacterManager::RegisterCharacter(ACharacter* Character)
{
	if (Character == nullptr)
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Trying to register a null character."));
		return false;
	}

	if (IsCharacterRegistered(Character) == true)
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Character has already been registered."));
		return false;
	}

	m_CharacterToPlayerMap.Emplace(Character, nullptr);
	return true;
}

bool ACharacterManager::RegisterPlayer(APlayerController* Player)
{
	if (Player == nullptr)
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Trying to register a null player."));
		return false;
	}

	if (IsPlayerRegistered(Player) == true)
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Player has already been registered."));
		return false;
	}

	m_PlayerToCharacterMap.Emplace(Player, nullptr);
	return true;
}

//UE_LOG
//(
//	LogCharacterManager,
//	Warning,
//	TEXT("Trying to register a player with an already assigned character. \
//		You should check that the character is available before trying to re-assign it.")
//);





