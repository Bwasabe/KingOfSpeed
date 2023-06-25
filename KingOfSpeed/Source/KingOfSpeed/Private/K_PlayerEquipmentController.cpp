// Fill out your copyright notice in the Description page of Project Settings.


#include "K_PlayerEquipmentController.h"
#include "K_Player.h"

#include "CableComponent.h"
#include "EnhancedInputComponent.h"
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

	m_PlayerHook = m_Owner->FindComponentByClass<UK_PlayerHook>();
	m_CurrentEquipment = m_PlayerHook;
}

void UK_PlayerEquipmentController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UK_PlayerEquipmentController::BindAction(UEnhancedInputComponent* EnhancedInputComp)
{
	EnhancedInputComp->BindAction(m_ExecuteAction, ETriggerEvent::Started, this, &UK_PlayerEquipmentController::Execute);
	EnhancedInputComp->BindAction(m_ExecuteAction, ETriggerEvent::Completed, this, &UK_PlayerEquipmentController::Release);
}
