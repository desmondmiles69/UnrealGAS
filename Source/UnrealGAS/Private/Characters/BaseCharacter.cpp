// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CustomAttributeSet.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAlive);
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

void ABaseCharacter::InitilizeAttributes() const
{
	checkf(IsValid(InitilizeAttributesEffect), TEXT("InitilizeAttributeEffect not set."));

	FGameplayEffectContextHandle effectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle effectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitilizeAttributesEffect, 1.f, effectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());

	Cast<UCustomAttributeSet>(GetAttributeSet())->PostAttributesInitilized();
}

void ABaseCharacter::ResetAttributes()
{
	checkf(IsValid(ResetAttributesEffect), TEXT("ResetAttributesEffect is not set"));

	// if(!HasAuthority())
	// {
	// 	return;
	// }

	FGameplayEffectContextHandle effectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle effectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(ResetAttributesEffect, 1.f, effectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());
}

void ABaseCharacter::OnHealthChanged(const FOnAttributeChangeData& ArrtibuteChangeData)
{
	if(ArrtibuteChangeData.NewValue <= 0.f)
	{
		HandleDeath();
	}
}

void ABaseCharacter::HandleDeath()
{
	bAlive = false;

	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%s has died"), *GetName()));
	}
}

void ABaseCharacter::HandleRespawn()
{
	bAlive = true;
}