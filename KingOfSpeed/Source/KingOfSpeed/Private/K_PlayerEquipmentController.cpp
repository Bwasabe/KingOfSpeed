// Fill out your copyright notice in the Description page of Project Settings.


#include "K_PlayerEquipmentController.h"
#include "K_Player.h"

#include "CableComponent.h"
#include "K_PlayerEquipmentBase.h"
#include "K_PlayerHook.h"
#include "K_PlayerMovement.h"
#include "GameFramework/CharacterMovementComponent.h"


void UK_PlayerEquipmentController::Execute(const FInputActionValue& Value)
{
	m_CurrentEquipment->Execute();
}

void UK_PlayerEquipmentController::Release(const FInputActionValue& Value)
{
	m_CurrentEquipment->Release();
}

void UK_PlayerEquipmentController::BeginPlay()
{
	Super::BeginPlay();

	m_CurrentEquipment = m_Owner->FindComponentByClass<UK_PlayerHook>();
}

void UK_PlayerEquipmentController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}
