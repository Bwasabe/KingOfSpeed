// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_PlayerComponentBase.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"


#include "K_PlayerMovement.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UK_PlayerMovement : public UK_PlayerComponentBase
{
	GENERATED_BODY()

public:
	UK_PlayerMovement();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Jump)
		int m_JumpMaxCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_SpeedMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_SpeedDecreaseTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_LogValue = 4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_MaxSpeed = 5000;

private:
	bool m_IsMoveSpeedLerping;

	float m_StartWalkSpeed;
	float m_LerpStartMoveSpeed;
	float m_MoveSpeedTimer;

	float m_MoveDurationTimer = 1.0f;

public:
	FVector2D m_MoveDir;

public:
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);

	void Turn(const FInputActionValue& Value);

private:
	bool DecreasePlayerSpeed(float DeltaTime);
};
