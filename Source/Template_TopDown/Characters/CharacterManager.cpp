// Fill out your copyright notice in the Description page of Project Settings.

#include "Template_TopDown.h"
#include "CharacterManager.h"
#include "GnCharacter.h"


ACharacterManager::ACharacterManager()
{
}

UWorld* ACharacterManager::GetWorld() const 
{ 
	checkf(m_World != nullptr, TEXT("Trying to use ACharacterManager with an null m_World."));
	return m_World; 
}

void ACharacterManager::Init(class UWorld* World)
{
	checkf(World != nullptr, TEXT("Trying to Init ACharacterManager with a null UWorld."));
	m_World = World;
}

void ACharacterManager::Reset()
{
	CharacterToPlayerMap.Empty(0);
	PlayerToCharacterMap.Empty(0);
}

bool ACharacterManager::IsCharacterAssigned(class AGnCharacter* Character, class AGnPlayerController* Player /*= nullptr*/)
{ 
	if (Player != nullptr)
		return CharacterToPlayerMap[Character] == Player;
	return CharacterToPlayerMap[Character] != nullptr; 
}

bool ACharacterManager::IsPlayerAssigned(class AGnPlayerController* Player, class AGnCharacter* Character /*= nullptr*/)
{
	if (Character != nullptr)
		return PlayerToCharacterMap[Player] == Character;
	return PlayerToCharacterMap[Player] != nullptr;
}

bool ACharacterManager::AssignCharacterToPlayer(class AGnPlayerController* Player, class AGnCharacter* NewCharacter /*= nullptr*/)
{
	if (NewCharacter != nullptr && IsCharacterAssigned(NewCharacter))
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Trying to assign a an already assigned character to another player."));
		return false;
	}

	// take the current character and clear its player
	AGnCharacter* const CurrentCharacter = PlayerToCharacterMap[Player];
	if (CurrentCharacter != nullptr)
	{
		CharacterToPlayerMap[CurrentCharacter] = nullptr;
	}
	// assign the new character to the player
	if (NewCharacter != nullptr)
	{
		CharacterToPlayerMap[NewCharacter] = Player;
	}

	PlayerToCharacterMap[Player] = NewCharacter;
	return true;
}

bool ACharacterManager::AssignPlayerToCharacter(class AGnCharacter* Character, class AGnPlayerController* NewPlayer /*= nullptr*/)
{
	if (NewPlayer != nullptr && IsPlayerAssigned(NewPlayer))
	{
		UE_LOG(LogCharacterManager, Warning, TEXT("Trying to assign a an already assigned player to another character."));
		return false;
	}

	// take the current player and clear its character
	AGnPlayerController* const CurrentPlayer = CharacterToPlayerMap[Character];
	if (CurrentPlayer != nullptr)
	{
		PlayerToCharacterMap[CurrentPlayer] = nullptr;
	}
	// assign the new player to the character
	if (NewPlayer != nullptr)
	{
		PlayerToCharacterMap[NewPlayer] = Character;
	}

	CharacterToPlayerMap[Character] = NewPlayer;
	return true;
}

AGnCharacter* ACharacterManager::CreateCharacter(UClass* Class, const FActorSpawnParameters& SpawnParameters)
{
	AGnCharacter* Character = GetWorld()->SpawnActor<AGnCharacter>(Class, SpawnParameters);
	if (Character == nullptr)
	{
		UE_LOG(LogCharacterManager, Error, TEXT("Couldn't create character."));
		return nullptr;
	}

	Character->SpawnDefaultController();
	return Character;
}

bool ACharacterManager::RegisterCharacter(AGnCharacter* Character)
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

	CharacterToPlayerMap.Emplace(Character, nullptr);
	return true;
}

bool ACharacterManager::RegisterPlayer(AGnPlayerController* Player)
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

	PlayerToCharacterMap.Emplace(Player, nullptr);
	return true;
}
