// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Defines/NetworkingDefines.h"

#include <GameFramework/GameModeBase.h>

#include "GenericGameMode.generated.h"

UCLASS(minimalapi)
class AGenericGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGenericGameMode();

	void PreLogin(const FString & Options, const FString & Address,	const FUniqueNetIdRepl& UniqueId,	FString & ErrorMessage) override;
	void PostLogin(APlayerController * NewPlayer) override;

	class ACharacterManager* GetCharacterManager() { return CharacterManager; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<APawn> CharacterClass;

	UPROPERTY(Transient)
	class ACharacterManager* CharacterManager;
};



