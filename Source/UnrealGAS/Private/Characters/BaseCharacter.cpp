// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "AbilitySystemComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ABaseCharacter::GiveStartupAbilities()
{
	if(!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}
	
	for(const TSubclassOf<UGameplayAbility> ability : StartupAbilities)
	{
		FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(ability);
		GetAbilitySystemComponent()->GiveAbility(abilitySpec);
	}
}

