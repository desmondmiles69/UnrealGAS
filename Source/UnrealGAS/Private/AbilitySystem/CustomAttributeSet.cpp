// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CustomAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UCustomAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME(ThisClass, bAttributesInitilized);
}

void UCustomAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	//PostAttributesInitilized();
}

void UCustomAttributeSet::OnRep_AttributesInitilized()
{
	if (bAttributesInitilized)
	{
		OnAttributesInitilized.Broadcast();
	}
}

void UCustomAttributeSet::OnRep_Health(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, oldValue);
}

void UCustomAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, oldValue);
}

void UCustomAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, oldValue);
}

void UCustomAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, oldValue);
}

void UCustomAttributeSet::PostAttributesInitilized()
{
	if(!bAttributesInitilized)
	{
		bAttributesInitilized = true;
		OnAttributesInitilized.Broadcast();
	}
}
