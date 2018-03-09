// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Defines/NetworkingDefines.h"

#include <GameFramework/GameModeBase.h>

#include "GnGameMode.generated.h"

class AGnCharacter;

UCLASS(minimalapi)
class AGnGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGnGameMode();

	class ACharacterManager* GetCharacterManager() const { return m_CharacterManager; }

protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	void PostLogin(APlayerController * NewPlayer) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
		TSubclassOf<AGnCharacter> CharacterClass;

	UPROPERTY(Transient)
		class ACharacterManager* m_CharacterManager;
};



