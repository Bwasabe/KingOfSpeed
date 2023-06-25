  // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"


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

	void ReStart(const FInputActionValue& InputActionValue);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* m_kMappingContext;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_RestartAction;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Restart)
		float m_RestartDuration = 0.5f;
	
	bool m_IsReadyToRestart = false;

	float m_RestartTimer;
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = Restart)
	FName m_LoadLevelName;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* m_PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterMesh)
		class USkeletalMeshComponent* m_PlayerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cable)
		class UCableComponent* m_Cable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerComponent)
		class UK_PlayerMovement* m_PlayerMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComponent)
		class UK_PlayerEquipmentController* m_PlayerEquipmentController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComponent)
		class UK_PlayerHook* m_PlayerHook;
public:
	UPROPERTY(VisibleAnywhere, Category = PlayerMesh)
		class USkeletalMeshComponent* m_PlayerGun;

public:
	class UUserWidget* m_RestartUI;
	
	UPROPERTY(EditDefaultsOnly, Category = ReStart)
		class TSubclassOf<class UUserWidget> m_RestartFactoryUI;

};
