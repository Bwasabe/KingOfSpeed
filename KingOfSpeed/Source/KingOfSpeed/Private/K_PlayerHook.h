// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_PlayerEquipmentBase.h"
#include "K_PlayerHook.generated.h"

/**
 * 
 */
UCLASS()
class UK_PlayerHook : public UK_PlayerEquipmentBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Execute() override;
	virtual void Release() override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_Distance = 3000.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_HookForce = 250000.0f;
	
private:
	class UK_PlayerMovement* m_PlayerMovement;

private:
	FVector m_GrabPoint;

private:
	bool m_IsGrappling;

public:
	bool GetIsGrappling() const {return m_IsGrappling;}
};
