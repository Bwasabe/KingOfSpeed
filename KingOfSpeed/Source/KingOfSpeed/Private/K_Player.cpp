// Fill out your copyright notice in the Description page of Project Settings.


#include "K_Player.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include <Camera/CameraComponent.h>
#include "K_PlayerEquipmentController.h"
#include "CableComponent.h"

#include "K_PlayerMovement.h"


// Sets default values
AK_Player::AK_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	

	// 카메라
	m_PlayerCamera = CreateDefaultSubobject<UCameraComponent>(L"PlayerCamera");
	if (m_PlayerCamera)
	{
		m_PlayerCamera->SetupAttachment(RootComponent);
		m_PlayerCamera->SetRelativeLocation(FVector(-10, 0, 60));
	}

	m_PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"PlayerMesh");
	if (m_PlayerMesh)
	{
		m_PlayerMesh->SetupAttachment(m_PlayerCamera);
	}

	// 움직임 컴포넌트
	m_PlayerMovement = CreateDefaultSubobject<UK_PlayerMovement>(L"PlayerMovement");

	// 장비 컨트롤러
	m_PlayerEquipmentController = CreateDefaultSubobject<UK_PlayerEquipmentController>(L"EquipmentController");

	// 케이블
	m_Cable = CreateDefaultSubobject<UCableComponent>(L"Cable");

	if(m_Cable)
	{
		m_Cable->SetupAttachment(m_PlayerCamera);
	}

}

// Called when the game starts or when spawned
void AK_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AK_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	EnhancedInputComp->BindAction(m_MoveAction, ETriggerEvent::Triggered, m_PlayerMovement, &UK_PlayerMovement::Move);

	// Jump
	EnhancedInputComp->BindAction(m_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComp->BindAction(m_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	//Turn
	EnhancedInputComp->BindAction(m_TurnAction, ETriggerEvent::Triggered, m_PlayerMovement, &UK_PlayerMovement::Turn);

	EnhancedInputComp->BindAction(m_ExecuteAction, ETriggerEvent::Started, m_PlayerEquipmentController, &UK_PlayerEquipmentController::Execute);
	EnhancedInputComp->BindAction(m_ExecuteAction, ETriggerEvent::Completed, m_PlayerEquipmentController, &UK_PlayerEquipmentController::Release);

}

