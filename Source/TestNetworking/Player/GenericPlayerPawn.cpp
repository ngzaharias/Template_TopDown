// Fill out your copyright notice in the Description page of Project Settings.

#include "TestNetworking.h"
#include "GenericPlayerPawn.h"

#include <Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h>
#include <Runtime/Engine/Classes/Components/DecalComponent.h>

AGenericPlayerPawn::AGenericPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Root);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Cursor = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	Cursor->SetupAttachment(Root);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Materials/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		Cursor->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	Cursor->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	Cursor->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

}

void AGenericPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AGenericPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Cursor != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			Cursor->SetWorldLocation(TraceHitResult.Location);
			Cursor->SetWorldRotation(CursorR);
		}
	}
}

// Called to bind functionality to input
void AGenericPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

