// Fill out your copyright notice in the Description page of Project Settings.


#include "K_Player.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AK_Player::AK_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AK_Player::BeginPlay()
{
	Super::BeginPlay();
	JumpMaxCount = m_JumpMaxCount;

	m_StartWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	m_LerpStartMoveSpeed = m_StartWalkSpeed;
	
}

// Called every frame
void AK_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!DecreasePlayerSpeed())
		GetCharacterMovement()->MaxWalkSpeed += GetWorld()->DeltaTimeSeconds * m_SpeedMultiplier;

}

bool AK_Player::DecreasePlayerSpeed()
{
	if(GetCharacterMovement()->IsFalling())
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, L"Falling");

	if (m_MoveDir == FVector2D::ZeroVector && !GetCharacterMovement()->IsFalling())
	{
		if (!m_IsMoveSpeedLerping)
		{
			m_IsMoveSpeedLerping = true;
			m_LerpStartMoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
		}

		m_MoveSpeedTimer += GetWorld()->DeltaTimeSeconds;

		GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(m_LerpStartMoveSpeed, m_StartWalkSpeed, m_MoveSpeedTimer / m_SpeedDecreaseTime);

		return true;
	}
	else
	{
		m_MoveSpeedTimer = .0f;
		m_IsMoveSpeedLerping = false;

		return false;
	}
}

void AK_Player::Move(const FInputActionValue& Value)
{
	// Value를 float으로 바꾼다
	m_MoveDir = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 플레이어의 회전값을 가져와서
		const FRotator rotation = Controller->GetControlRotation();
		// 회전값 중 Yaw회전값을 가져온 후
		const FRotator yawRotation(0, rotation.Yaw, 0);

		// 그 YawRotation의 회전 행렬을 만들어 X방향(전방)의 방향을 가져온다
		const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwardDir, m_MoveDir.Y);
		AddMovementInput(rightDir, m_MoveDir.X);

	}
}

// Called to bind functionality to input
void AK_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(m_kMappingContext, 0);
		}
	}
	

	UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInputComp)return;
	
	//Move
	EnhancedInputComp->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &AK_Player::Move);

	// Jump
	EnhancedInputComp->BindAction(m_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComp->BindAction(m_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	//Turn
	EnhancedInputComp->BindAction(m_TurnAction, ETriggerEvent::Triggered, this, &AK_Player::Turn);
}

void AK_Player::Turn(const FInputActionValue& Value)
{
	FVector2D turn = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(turn.X);
		AddControllerPitchInput(-turn.Y);
	}
}
