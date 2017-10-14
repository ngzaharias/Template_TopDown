// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Template_TopDown.h"
#include "GenericCharacter.h"

AGenericCharacter::AGenericCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AGenericCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	
}

void AGenericCharacter::MoveToLocation(FVector Location)
{

}
