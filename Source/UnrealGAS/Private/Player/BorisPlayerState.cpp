// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BorisPlayerState.h"
#include "AbilitySystem/CustomAbilitySystemComponent.h"
#include "AbilitySystem/CustomAttributeSet.h"

ABorisPlayerState::ABorisPlayerState()
{
	 SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UCustomAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UCustomAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ABorisPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
