// Fill out your copyright notice in the Description page of Project Settings.

#include "TestNetworking.h"
#include "CharacterManager.h"
#include "GenericCharacter.h"


ACharacterManager::ACharacterManager()
{
}

void ACharacterManager::Init()
{
}

void ACharacterManager::Reset()
{
	Characters.Empty();
	CharacterToPlayerMap.Empty(0);
	PlayerToCharacterMap.Empty(0);
}

bool ACharacterManager::AssignCharacterToPlayer(ACharacter* Character, APlayerController* Player)
{
	if (IsCharacterAssigned(Character) == true)
		return false;

	// clear the player for the current player's character
	const ACharacter* const CurrentCharacter = PlayerToCharacterMap[Player];
	CharacterToPlayerMap[CurrentCharacter] = NULL;

	// assign the new character to the player
	CharacterToPlayerMap[Character] = Player;
	PlayerToCharacterMap[Player] = Character;
	return true;
}

bool ACharacterManager::CreateCharacter(UClass* Class, const FActorSpawnParameters& SpawnParameters, ACharacter* out_Character, APlayerController* OwningPlayer /*= NULL*/)
{
	//out_Character = GetWorld()->SpawnActor<ACharacter>(Class, SpawnParameters);
	if (out_Character == NULL)
		return false;

	return RegisterCharacter(out_Character, OwningPlayer);
}

bool ACharacterManager::RegisterCharacter(ACharacter* Character, APlayerController* OwningPlayer /*= NULL*/)
{
	if (Character == NULL)
		return false;

	if (IsCharacterRegistered(Character) == true)
		return false;

	Characters.Add(Character);
	CharacterToPlayerMap[Character] = OwningPlayer;
	PlayerToCharacterMap[OwningPlayer] = Character;
	return true;
}

bool ACharacterManager::RegisterPlayer(APlayerController* Player, ACharacter* Character)
{
	if (Character == NULL || Player == NULL)
		return false;

	if (IsCharacterAssigned(Character) == true)
		return false;

	Characters.AddUnique(Character);
	CharacterToPlayerMap[Character] = Player;
	PlayerToCharacterMap[Player] = Character;
	return true;
}





