// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include <GameFramework/Character.h>
#include "GnCharacter.generated.h"

class USceneComponent;

UCLASS(Blueprintable)
class AGnCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGnCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaSeconds) override;

	void MoveToLocation(FVector Location);
};

