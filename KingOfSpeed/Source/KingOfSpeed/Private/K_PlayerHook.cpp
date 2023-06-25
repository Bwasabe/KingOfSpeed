// Fill out your copyright notice in the Description page of Project Settings.


#include "K_PlayerHook.h"

#include "CableComponent.h"
#include "K_Player.h"
#include "K_PlayerMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UK_PlayerHook::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerMovement = m_Owner->m_PlayerMovement;

	m_PlayerController = GetWorld()->GetFirstPlayerController();

	if(!m_PlayerController)
		UE_LOG(LogTemp, Log, L"Controller가 없음");
}

void UK_PlayerHook::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!m_IsGrappling)return;

	
	m_Owner->m_Cable->EndLocation = m_Owner->GetActorTransform().InverseTransformPositionNoScale(m_GrabPoint);

	FVector forceVector = m_GrabPoint - m_Owner->GetActorLocation() + m_Owner->m_PlayerCamera->GetForwardVector() + m_Owner->GetActorRightVector() * m_PlayerMovement->m_MoveDir.X;
	forceVector.Normalize();
	

	m_Owner->GetCharacterMovement()->AddForce(forceVector * m_HookForce);
}

void UK_PlayerHook::Execute()
{
	FVector startPos = m_Owner->m_PlayerCamera->GetComponentLocation();
	FVector endPos = startPos + m_Owner->m_PlayerCamera->GetForwardVector() * m_Distance;
	
	FHitResult hitResult;
	FCollisionResponseParams collisionResponseParam;
	
	FCollisionQueryParams queryParam;
	queryParam.AddIgnoredActor(m_Owner);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECollisionChannel::ECC_Visibility, queryParam, collisionResponseParam))
	{
		m_PlayerController->PlayerCameraManager->StartCameraShake(m_CameraShake);
		
		m_IsGrappling = true;

		int jumpCurrentCount = m_Owner->JumpCurrentCount;
		
		m_Owner->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		
		m_GrabPoint = hitResult.ImpactPoint;

		m_Owner->m_Cable->SetVisibility(true);
		
		m_Owner->JumpCurrentCount = jumpCurrentCount - 1;
	}
}

void UK_PlayerHook::Release()
{
	if(!m_IsGrappling)return;
	
	m_IsGrappling = false;
	m_Owner->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	m_Owner->m_Cable->SetVisibility(false);
}
