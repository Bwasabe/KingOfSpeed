// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"

#include "K_Player.generated.h"

UCLASS()
class AK_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AK_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* m_kMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* m_MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* m_JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* m_TurnAction;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Jump)
		int m_JumpMaxCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_SpeedMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Move)
		float m_SpeedDecreaseTime;

private:
	bool m_IsMoveSpeedLerping;

	float m_StartWalkSpeed;
	float m_LerpStartMoveSpeed;
	float m_MoveSpeedTimer;


	FVector2D m_MoveDir;

private:
	bool DecreasePlayerSpeed();
	
private:
	void Move(const FInputActionValue& Value);

	void Turn(const FInputActionValue& Value);
};
