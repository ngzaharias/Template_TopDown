// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Template_TopDown.h"
#include "GnCharacter.h"

AGnCharacter::AGnCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->InitCapsuleSize(42.f, 96.0f);

	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	CharacterMovement->bOrientRotationToMovement = true;
	CharacterMovement->RotationRate = FRotator(0.f, 320.f, 0.f);
	CharacterMovement->bConstrainToPlane = true;
	CharacterMovement->bSnapToPlaneAtStart = true;

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	SkeletalMesh->SetRelativeLocation(FVector(0, 0, -Capsule->GetScaledCapsuleHalfHeight()));
	SkeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AGnCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	
}

void AGnCharacter::MoveToLocation(FVector Location)
{

}
