// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeChangeTask.h"
#include "AbilitySystemComponent.h"

UAttributeChangeTask* UAttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* abilitySystemComponent, FGameplayAttribute attribute)
{
	UAttributeChangeTask* WaitForAttributeChangeTask = NewObject<UAttributeChangeTask>();
	WaitForAttributeChangeTask->ASC = abilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = attribute;

	if(!IsValid(abilitySystemComponent))
	{
		WaitForAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(attribute).AddUObject(WaitForAttributeChangeTask, &UAttributeChangeTask::AttributeChanged);
	return WaitForAttributeChangeTask;
}

void UAttributeChangeTask::Endtask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UAttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& data)
{
	OnAttributeChanged.Broadcast(data.Attribute, data.NewValue, data.OldValue);
}
