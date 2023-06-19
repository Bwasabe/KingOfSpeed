// Fill out your copyright notice in the Description page of Project Settings.


#include "K_PlayerEquipmentController.h"
#include "K_Player.h"
#include <Camera/CameraComponent.h>

#include "CableComponent.h"
#include "K_PlayerMovement.h"
#include "GameFramework/CharacterMovementComponent.h"


void UK_PlayerEquipmentController::Execute(const FInputActionValue& Value)
{
	FVector startPos = m_Owner->m_PlayerCamera->GetComponentLocation();
	FVector endPos = startPos + m_Owner->m_PlayerCamera->GetForwardVector() * m_Distance;
	
	FHitResult hitResult;
	FCollisionResponseParams collisionResponseParam;
	
	FCollisionQueryParams queryParam;
	queryParam.AddIgnoredActor(m_Owner);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECollisionChannel::ECC_Visibility, queryParam, collisionResponseParam))
	{
		m_IsGrappling = true;
		m_Owner->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		
		m_GrabPoint = hitResult.ImpactPoint;

		m_Owner->m_Cable->SetVisibility(true);
		
		m_Owner->JumpCurrentCount--;
		
		//	DrawDebugLine(GetWorld(), startPos, hitResult.ImpactPoint, FColor::Green, true, 100.0f, 0, 12.3f);
	}
	//m_CurrentEquipment->Execute();
}

void UK_PlayerEquipmentController::Release(const FInputActionValue& Value)
{
	if(!m_IsGrappling)return;
	
	m_IsGrappling = false;
	m_Owner->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	m_Owner->m_Cable->SetVisibility(false);

}

void UK_PlayerEquipmentController::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerMovement = m_Owner->FindComponentByClass<UK_PlayerMovement>();
}

void UK_PlayerEquipmentController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!m_IsGrappling)return;

	
	 m_Owner->m_Cable->EndLocation = m_Owner->GetActorTransform().InverseTransformPositionNoScale(m_GrabPoint);

	FVector forceVector = m_GrabPoint - m_Owner->GetActorLocation() + m_Owner->GetActorRightVector() * m_PlayerMovement->m_MoveDir.X;
	forceVector.Normalize();
	

	m_Owner->GetCharacterMovement()->AddForce(forceVector * m_HookForce);
}
