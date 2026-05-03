// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BorisPlayerState.h"
#include "AbilitySystemComponent.h"

ABorisPlayerState::ABorisPlayerState()
{
	 SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ABorisPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
