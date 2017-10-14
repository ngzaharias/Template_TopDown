// Fill out your copyright notice in the Description page of Project Settings.

#include "Template_TopDown.h"
#include "GenericPlayerPawn.h"

#include <Components/DecalComponent.h>
#include <GameFramework/FloatingPawnMovement.h>
#include <UObject/ConstructorHelpers.h>

AGenericPlayerPawn::AGenericPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = m_Root;

	m_CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_CameraBoom->SetupAttachment(m_Root);
	m_CameraBoom->bAbsoluteRotation = true;
	m_CameraBoom->TargetArmLength = 800.f;
	m_CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	m_CameraBoom->bDoCollisionTest = false;
	m_CameraBoom->bEnableCameraLag = true;
	m_CameraBoom->CameraLagSpeed = 3.0f;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_CameraBoom, USpringArmComponent::SocketName);
	m_Camera->bUsePawnControlRotation = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	m_Cursor = CreateDefaultSubobject<UDecalComponent>(TEXT("Cursos"));
	m_Cursor->SetupAttachment(m_Root);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Materials/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		m_Cursor->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	m_Cursor->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	m_Cursor->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	m_MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	m_MovementComponent->UpdatedComponent = RootComponent;

	bOnlyRelevantToOwner = true;
	bReplicates = false;
}

void AGenericPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AGenericPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Cursor != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorV.Rotation();
			m_Cursor->SetWorldLocation(TraceHitResult.Location);
			m_Cursor->SetWorldRotation(CursorR);
		}
	}
}

// Called to bind functionality to input
void AGenericPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGenericPlayerPawn::AdjustYaw(const float AxisValue)
{
	if (m_bIsCameraRotateEnabled)
	{
		FRotator yaw(0.f, AxisValue * m_AdjustYawSpeed, 0.f);
		AddActorLocalRotation(yaw);
		m_CameraBoom->AddWorldRotation(yaw);
	}
}

void AGenericPlayerPawn::AdjustZoom(const float AxisValue)
{
	m_CameraBoom->TargetArmLength += AxisValue;
}

void AGenericPlayerPawn::MoveHorizontal(const float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AGenericPlayerPawn::MoveVertical(const float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AGenericPlayerPawn::ToggleYawAdjustments()
{
	m_bIsCameraRotateEnabled = !m_bIsCameraRotateEnabled;
}
