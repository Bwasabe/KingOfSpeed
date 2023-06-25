// Fill out your copyright notice in the Description page of Project Settings.


#include "K_Player.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include <Camera/CameraComponent.h>
#include "K_PlayerEquipmentController.h"
#include "CableComponent.h"
#include "K_PlayerHook.h"

#include <Blueprint/UserWidget.h>

#include "K_PlayerComponentBase.h"

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

	// 훅
	m_PlayerHook = CreateDefaultSubobject<UK_PlayerHook>(L"PlayerHook");

	// 총 메시 로드
	m_PlayerGun = CreateDefaultSubobject<USkeletalMeshComponent>(L"PlayerGun");
	if(m_PlayerGun)
	{	
		m_PlayerGun->SetupAttachment(m_PlayerMesh, TEXT("hand_r"));

		// 스켈레탈 메시 데이터 로드
		ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));

		if (TempGunMesh.Succeeded())
		{
			m_PlayerGun->SetSkeletalMesh(TempGunMesh.Object);
			m_PlayerGun->SetRelativeLocation(FVector(-17,  10, -3));
			m_PlayerGun->SetRelativeRotation(FRotator(0, 90, 0));
		}

		// 케이블
		m_Cable = CreateDefaultSubobject<UCableComponent>(L"Cable");
		if(m_Cable)
		{
			m_Cable->SetupAttachment(m_PlayerGun, L"Muzzle");
		}
	}
	
	
}

// Called when the game starts or when spawned
void AK_Player::BeginPlay()
{
	Super::BeginPlay();

	m_AimUI = CreateWidget(GetWorld(), m_AimFactoryUI);
	
	if(m_AimUI)
		m_AimUI->AddToViewport();
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


	TInlineComponentArray<UK_PlayerComponentBase*> components;

	GetComponents(components);
	for(auto* component : components)
	{
		component->BindAction(EnhancedInputComp);
	}

}

