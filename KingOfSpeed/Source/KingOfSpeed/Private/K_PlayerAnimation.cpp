// Fill out your copyright notice in the Description page of Project Settings.


#include "K_PlayerAnimation.h"

#include "K_Player.h"
#include "K_PlayerHook.h"
#include "GameFramework/CharacterMovementComponent.h"

void UK_PlayerAnimation::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto pawn = TryGetPawnOwner();
	m_Player = Cast<AK_Player>(pawn);
}

void UK_PlayerAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(m_Player)
	{
		const auto movement = m_Player->GetCharacterMovement();
		
		if(movement)
		{
		    m_AnimSpeed = movement->MaxWalkSpeed;
		
		    m_IsJumping = movement->IsFalling();
		}

		m_IsShoot = m_Player->m_PlayerHook->GetIsGrappling();
	}
}
