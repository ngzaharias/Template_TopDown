// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Info.h>
#include "CharacterManager.generated.h"

/**
 *
 */
UCLASS(NotPlaceable)
class TESTNETWORKING_API ACharacterManager
	: public AInfo
{
	GENERATED_BODY()

public:
	ACharacterManager();

	UWorld* GetWorld() const override;

	void Init(class UWorld* World);
	void Reset();

	class ACharacter* GetCharacterFromPlayer(class APlayerController* Player) { return m_PlayerToCharacterMap[Player]; }
	class APlayerController* GetPlayerFromCharacter(class ACharacter* Character) { return m_CharacterToPlayerMap[Character]; }

	bool IsCharacterAssigned(class ACharacter* Character, class APlayerController* Player = nullptr);
	bool IsPlayerAssigned(class APlayerController* Player, class ACharacter* Character = nullptr);

	bool IsCharacterRegistered(class ACharacter* Character) { return m_CharacterToPlayerMap.Contains(Character); }
	bool IsPlayerRegistered(class APlayerController* Player) { return m_PlayerToCharacterMap.Contains(Player); }

	class ACharacter* CreateCharacter(class UClass* Class, const FActorSpawnParameters& SpawnParameters);

	bool AssignCharacterToPlayer(class APlayerController* Player, class ACharacter* Character = nullptr);
	bool AssignPlayerToCharacter(class ACharacter* Character, class APlayerController* Player = nullptr);

	bool RegisterCharacter(class ACharacter* Character);
	bool RegisterPlayer(class APlayerController* Player);


protected:
	UPROPERTY()
		TMap<class ACharacter*, class APlayerController*> m_CharacterToPlayerMap;

	UPROPERTY()
		TMap<class APlayerController*, class ACharacter*> m_PlayerToCharacterMap;

private:
	class UWorld* m_World = nullptr;

};
