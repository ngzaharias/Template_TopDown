// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Info.h"
#include "CharacterManager.generated.h"

/**
 * 
 */
UCLASS()
class TESTNETWORKING_API ACharacterManager : public AInfo
{
	GENERATED_BODY()

public:
	ACharacterManager();

	void Init();
	void Reset();

	class ACharacter* GetPlayersCharacter(class APlayerController* Player) { return PlayerToCharacterMap[Player]; }
	class APlayerController* GetCharactersPlayer(class ACharacter* Character) { return CharacterToPlayerMap[Character]; }

	bool IsCharacterAssigned(class ACharacter* Character) { return CharacterToPlayerMap[Character] != NULL; }
	bool IsCharacterRegistered(class ACharacter* Character) { return Characters.Find(Character) != INDEX_NONE; }

	bool AssignCharacterToPlayer(class ACharacter* Character, class APlayerController* OwningPlayer);
	bool CreateCharacter(class UClass* Class, const FActorSpawnParameters& SpawnParameters, class ACharacter* out_Character, APlayerController* OwningPlayer = NULL);
	bool RegisterCharacter(class ACharacter* Character, class APlayerController* Player = NULL);
	bool RegisterPlayer(class APlayerController* Player, class ACharacter* Character);

	
protected:
	UPROPERTY() 
	TArray<class ACharacter*> Characters;

	UPROPERTY() 
	TMap<class ACharacter*, class APlayerController*> CharacterToPlayerMap;

	UPROPERTY() 
	TMap<class APlayerController*, class ACharacter*> PlayerToCharacterMap;
	
};
