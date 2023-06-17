// Fill out your copyright notice in the Description page of Project Settings.


#include "K_Player.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "C:/Unreal/Editor/UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

#include "K_PlayerMovement.h"


// Sets default values
AK_Player::AK_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_PlayerMovement = CreateDefaultSubobject<UK_PlayerMovement>(L"PlayerMovement");

}

// Called when the game starts or when spawned
void AK_Player::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement();
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
}

