// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CustomAbilitySystemComponent.h"
#include "GameplayTags/Tags.h"

void UCustomAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	HandleAutoActivatedAbility(AbilitySpec);
}

void UCustomAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	FScopedAbilityListLock abilityListLock(*this);
	for (const FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities())
	{
		HandleAutoActivatedAbility(abilitySpec);
		return; 
	}
}

void UCustomAbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level)
{
	if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;

	if (FGameplayAbilitySpec* abilitySpec = FindAbilitySpecFromClass(abilityClass))
	{
		abilitySpec->Level += level;
		MarkAbilitySpecDirty(*abilitySpec);
	}
}

void UCustomAbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level)
{
	if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;

	if (FGameplayAbilitySpec* abilitySpec = FindAbilitySpecFromClass(abilityClass))
	{
		abilitySpec->Level = level;
		MarkAbilitySpecDirty(*abilitySpec);
	}
}

void UCustomAbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& abilitySpec)
{
	if (!IsValid(abilitySpec.Ability))
	{
		return;
	}

	for (const FGameplayTag& abilityTag : abilitySpec.Ability->GetAssetTags())
	{
		if (abilityTag.MatchesTagExact(Tags::AbilityTags::ActivateOnGiven))
		{
			TryActivateAbility(abilitySpec.Handle);
			return;
		}
	}
}
