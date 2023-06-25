// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_PlayerComponentBase.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"


#include "K_PlayerEquipmentController.generated.h"

enum class PlayerEquipment : uint8 {
	Hook,
	Shoot,
	
	Length
};

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
	virtual void BindAction(UEnhancedInputComponent* EnhancedInputComp) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_ExecuteAction;
private:
	class UK_PlayerEquipmentBase* m_CurrentEquipment;
	
	class UK_PlayerHook* m_PlayerHook;
	class UK_PlayerShoot* m_PlayerShoot;
};
