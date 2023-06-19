// Fill out your copyright notice in the Description page of Project Settings.


#include "K_PlayerMovement.h"
#include "K_PlayerComponentBase.h"
#include <GameFramework/CharacterMovementComponent.h>

#include "K_Player.h"


UK_PlayerMovement::UK_PlayerMovement() : UK_PlayerComponentBase()
{}

void UK_PlayerMovement::BeginPlay()
{
	UK_PlayerComponentBase::BeginPlay();

	m_Owner->JumpMaxCount = m_JumpMaxCount;

	m_StartWalkSpeed = m_Owner->GetCharacterMovement()->MaxWalkSpeed;

	m_LerpStartMoveSpeed = m_Owner->GetCharacterMovement()->MaxWalkSpeed;
}

void UK_PlayerMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UK_PlayerComponentBase::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DecreasePlayerSpeed(DeltaTime))
	{
		m_MoveDurationTimer = 1.0f;	
	}
	else
	{
		m_MoveDurationTimer += DeltaTime;

		m_Owner->GetCharacterMovement()->MaxWalkSpeed += FMath::LogX(m_LogValue, m_MoveDurationTimer) * m_SpeedMultiplier * DeltaTime;
	}
}

bool UK_PlayerMovement::DecreasePlayerSpeed(const float DeltaTime)
{
	if (m_MoveDir == FVector2D::ZeroVector && !m_Owner->GetCharacterMovement()->IsFalling())
	{
		if (!m_IsMoveSpeedLerping)
		{
			m_IsMoveSpeedLerping = true;
			m_LerpStartMoveSpeed = m_Owner->GetCharacterMovement()->MaxWalkSpeed;
		}

		m_MoveSpeedTimer += DeltaTime;

		m_Owner->GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(m_LerpStartMoveSpeed, m_StartWalkSpeed, m_MoveSpeedTimer / m_SpeedDecreaseTime);

		return true;
	}
	else
	{
		m_MoveSpeedTimer = .0f;
		m_IsMoveSpeedLerping = false;

		if (m_Owner->GetCharacterMovement()->MaxWalkSpeed < m_StartWalkSpeed)
		{
			m_Owner->GetCharacterMovement()->MaxWalkSpeed = m_StartWalkSpeed;
		}
		return false;
	}
}


void UK_PlayerMovement::Move(const FInputActionValue& Value)
{
	// Value�� float���� �ٲ۴�
	m_MoveDir = Value.Get<FVector2D>();

	if (m_Owner->Controller != nullptr)
	{
		// �÷��̾��� ȸ������ �����ͼ�
		const FRotator rotation = m_Owner->Controller->GetControlRotation();
		// ȸ���� �� Yawȸ������ ������ ��
		const FRotator yawRotation(0, rotation.Yaw, 0);

		// �� YawRotation�� ȸ�� ����� ����� X����(����)�� ������ �����´�
		const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		m_MoveDir.Normalize();
		//UE_LOG(LogTemp, Log, L"%s", *m_MoveDir.ToString());


		m_Owner->AddMovementInput(forwardDir, m_MoveDir.Y);
		m_Owner->AddMovementInput(rightDir, m_MoveDir.X);

	}
}

void UK_PlayerMovement::Turn(const FInputActionValue& Value)
{
	FVector2D turn = Value.Get<FVector2D>();
	if (m_Owner->Controller != nullptr)
	{
		m_Owner->AddControllerYawInput(turn.X);
		m_Owner->AddControllerPitchInput(-turn.Y);
	}
}