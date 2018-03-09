// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Info.h>
#include "CharacterManager.generated.h"

class AGnCharacter;
class AGnPlayerController;
class UWorld;

/**
 *
 */
UCLASS(NotPlaceable)
class TEMPLATE_TOPDOWN_API ACharacterManager
	: public AInfo
{
	typedef TMap<AGnCharacter*, AGnPlayerController*> TCharacterToPlayerMap;
	typedef TMap<AGnPlayerController*, AGnCharacter*> TPlayerToCharacterMap;

	GENERATED_BODY()

public:
	ACharacterManager();

	UWorld* GetWorld() const override;

	void Init(class UWorld* World);
	void Reset();

	UFUNCTION(BlueprintCallable)
		AGnCharacter* GetCharacterFromPlayer(class AGnPlayerController* Player) { return PlayerToCharacterMap[Player]; }
	UFUNCTION(BlueprintCallable)
		AGnPlayerController* GetPlayerFromCharacter(class AGnCharacter* Character) { return CharacterToPlayerMap[Character]; }

	bool IsCharacterAssigned(class AGnCharacter* Character, class AGnPlayerController* Player = nullptr);
	bool IsPlayerAssigned(class AGnPlayerController* Player, class AGnCharacter* Character = nullptr);

	bool IsCharacterRegistered(class AGnCharacter* Character) { return CharacterToPlayerMap.Contains(Character); }
	bool IsPlayerRegistered(class AGnPlayerController* Player) { return PlayerToCharacterMap.Contains(Player); }

	class AGnCharacter* CreateCharacter(class UClass* Class, const FActorSpawnParameters& SpawnParameters);

	bool AssignCharacterToPlayer(class AGnPlayerController* Player, class AGnCharacter* Character = nullptr);
	bool AssignPlayerToCharacter(class AGnCharacter* Character, class AGnPlayerController* Player = nullptr);

	bool RegisterCharacter(class AGnCharacter* Character);
	bool RegisterPlayer(class AGnPlayerController* Player);


protected:
	TCharacterToPlayerMap CharacterToPlayerMap;
	TPlayerToCharacterMap PlayerToCharacterMap;

private:
	class UWorld* m_World = nullptr;

};
