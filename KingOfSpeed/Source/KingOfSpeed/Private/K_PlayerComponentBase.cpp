// Fill out your copyright notice in the Description page of Project Settings.

#include "K_PlayerComponentBase.h"
#include "K_Player.h"

// Sets default values for this component's properties
UK_PlayerComponentBase::UK_PlayerComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UK_PlayerComponentBase::BeginPlay()
{
	Super::BeginPlay();

	m_Owner = Cast<AK_Player>(GetOwner());
	
}


// Called every frame
void UK_PlayerComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

