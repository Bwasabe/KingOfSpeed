// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_PlayerComponentBase.h"
#include "K_PlayerEquipmentBase.generated.h"

/**
 * 
 */
UCLASS(abstract)
class UK_PlayerEquipmentBase : public UK_PlayerComponentBase
{
	GENERATED_BODY()

public:
	virtual void Execute() PURE_VIRTUAL(UK_PlayerEquipmentBase::Execute, );
	virtual  void Release() PURE_VIRTUAL(UK_PlayerEquipmentBase::Release, );
};
