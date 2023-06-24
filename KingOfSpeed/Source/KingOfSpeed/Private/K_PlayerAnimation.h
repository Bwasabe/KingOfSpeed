// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_PlayerComponentBase.h"
#include "K_PlayerAnimation.generated.h"

/**
 * 
 */
UCLASS()
class UK_PlayerAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

private:
	AK_Player* m_Player;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=PlayerAnim)
    	float m_AnimSpeed = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=PlayerAnim)
		bool m_IsShoot;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=PlayerAnim)
		bool m_IsJumping;	
	
};
