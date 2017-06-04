// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include <GameFramework/Character.h>
#include "GenericCharacter.generated.h"

UCLASS(Blueprintable)
class AGenericCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGenericCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

};

