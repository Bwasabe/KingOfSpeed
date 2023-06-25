// Fill out your copyright notice in the Description page of Project Settings.


#include "K_PlayerMovement.h"
#include "K_PlayerComponentBase.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

#include "K_Player.h"


UK_PlayerMovement::UK_PlayerMovement() : UK_PlayerComponentBase()
{
}

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

	const bool isGrappling = m_Owner->GetCharacterMovement()->GetGroundMovementMode() == EMovementMode::MOVE_Flying;
	if(DecreasePlayerSpeed(DeltaTime) && !isGrappling)
	{
		m_MoveDurationTimer = 1.0f;
	}
	else
	{
		if(!m_Owner->GetCharacterMovement()->IsFalling())
		{
			m_MoveDurationTimer += DeltaTime;
			
			m_CurrentSpeed += FMath::LogX(m_LogValue, m_MoveDurationTimer) * m_SpeedMultiplier * DeltaTime;
		}
	}
	
	m_CurrentSpeed = FMath::Clamp(m_CurrentSpeed, m_StartWalkSpeed, m_MaxSpeed);
	m_Owner->GetCharacterMovement()->MaxWalkSpeed = m_CurrentSpeed;
}

void UK_PlayerMovement::BindAction(UEnhancedInputComponent* EnhancedInputComp)
{
	// Move
	EnhancedInputComp->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &UK_PlayerMovement::Move);

	// Jump
	EnhancedInputComp->BindAction(m_JumpAction, ETriggerEvent::Triggered, this, &UK_PlayerMovement::Jump);
	EnhancedInputComp->BindAction(m_JumpAction, ETriggerEvent::Completed, m_Owner, &ACharacter::StopJumping);

	//Turn
	EnhancedInputComp->BindAction(m_TurnAction, ETriggerEvent::Triggered, this, &UK_PlayerMovement::Turn);
}

bool UK_PlayerMovement::DecreasePlayerSpeed(const float DeltaTime)
{
	if(m_MoveDir == FVector2D::ZeroVector && !m_Owner->GetCharacterMovement()->IsFalling())
	{
		if(!m_IsMoveSpeedLerping)
		{
			m_IsMoveSpeedLerping = true;
			m_LerpStartMoveSpeed = m_Owner->GetCharacterMovement()->MaxWalkSpeed;
		}

		m_MoveSpeedTimer += DeltaTime;

		float lerpValue = m_MoveSpeedTimer / m_SpeedDecreaseTime;

		m_CurrentSpeed = FMath::Lerp(m_LerpStartMoveSpeed, m_StartWalkSpeed, lerpValue);

		return true;
	}
	else
	{
		m_MoveSpeedTimer = .0f;
		m_IsMoveSpeedLerping = false;

		return false;
	}
}


void UK_PlayerMovement::Move(const FInputActionValue& Value)
{
	// Value�� float���� �ٲ۴�
	m_MoveDir = Value.Get<FVector2D>();

	if(m_Owner->Controller != nullptr)
	{
		// �÷��̾��� ȸ������ �����ͼ�
		const FRotator rotation = m_Owner->Controller->GetControlRotation();
		// ȸ���� �� Yawȸ������ ������ ��
		const FRotator yawRotation(0, rotation.Yaw, 0);

		// �� YawRotation�� ȸ�� ����� ����� X����(����)�� ������ �����´�
		const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		m_MoveDir.Normalize();

		m_Owner->AddMovementInput(forwardDir, m_MoveDir.Y);
		m_Owner->AddMovementInput(rightDir, m_MoveDir.X);

	}
}

void UK_PlayerMovement::Jump(const FInputActionValue& Value)
{
	const bool isFirstJump = m_Owner->JumpCurrentCount == 0;

	if(isFirstJump)
	{
		if(m_Owner->GetCharacterMovement()->IsFalling())
		{
			m_Owner->JumpMaxCount = m_JumpMaxCount + 1;
		}
		else
		{
			m_Owner->JumpMaxCount = m_JumpMaxCount;
		}
	}

	m_Owner->Jump();
}


void UK_PlayerMovement::Turn(const FInputActionValue& Value)
{
	FVector2D turn = Value.Get<FVector2D>();
	if(m_Owner->Controller != nullptr)
	{
		m_Owner->AddControllerYawInput(turn.X);
		m_Owner->AddControllerPitchInput(-turn.Y);
	}
}
