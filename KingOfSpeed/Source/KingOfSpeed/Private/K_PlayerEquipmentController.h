// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_PlayerComponentBase.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"


#include "K_PlayerEquipmentController.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UK_PlayerEquipmentController : public UK_PlayerComponentBase
{
	GENERATED_BODY()

public:
	void Execute(const FInputActionValue& Value);
	void Release(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	class UK_PlayerEquipmentBase* m_CurrentEquipment;

};
