// Fill out your copyright notice in the Description page of Project Settings.

#include "Template_TopDown.h"
#include "GnPlayerPawn.h"

#include <Components/DecalComponent.h>
#include <GameFramework/FloatingPawnMovement.h>
#include <Kismet/KismetMathLibrary.h>
#include <UObject/ConstructorHelpers.h>

AGnPlayerPawn::AGnPlayerPawn()
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

void AGnPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	m_TargetArmLength = m_CameraBoom->TargetArmLength;
	m_TargetArmPitch = m_CameraBoom->GetComponentRotation().Pitch;
}

void AGnPlayerPawn::Tick(float DeltaTime)
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

	m_CameraBoom->TargetArmLength = UKismetMathLibrary::Lerp(m_CameraBoom->TargetArmLength, m_TargetArmLength, 0.1f);

	FRotator NewRotation = m_CameraBoom->GetComponentRotation();
	NewRotation.Pitch = UKismetMathLibrary::Lerp(NewRotation.Pitch, m_TargetArmPitch, 0.1f);
	m_CameraBoom->SetRelativeRotation(NewRotation);
}

// Called to bind functionality to input
void AGnPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGnPlayerPawn::AdjustYaw(const float AxisValue)
{
	if (m_bIsCameraRotateEnabled)
	{
		FRotator yaw(0.f, AxisValue * m_AdjustYawSpeed, 0.f);
		AddActorLocalRotation(yaw);
		m_CameraBoom->AddWorldRotation(yaw);
	}
}

void AGnPlayerPawn::AdjustZoom(const float AxisValue)
{
	m_TargetArmLength += AxisValue * m_AdjustZoomSpeed;
	m_TargetArmLength = FMath::Clamp(m_TargetArmLength, m_SpringDistanceMin, m_SpringDistanceMax);

	float alpha = (m_TargetArmLength + m_SpringDistanceMin) / (m_SpringDistanceMax + m_SpringDistanceMin);
	m_TargetArmPitch = UKismetMathLibrary::Lerp(m_CameraPitchMin, m_CameraPitchMax, alpha);
}

void AGnPlayerPawn::MoveHorizontal(const float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AGnPlayerPawn::MoveVertical(const float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AGnPlayerPawn::ToggleYawAdjustments()
{
	m_bIsCameraRotateEnabled = !m_bIsCameraRotateEnabled;
}
