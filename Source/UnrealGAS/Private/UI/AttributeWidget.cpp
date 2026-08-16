// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AttributeWidget.h"

void UAttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UAttributeSet* AttributeSet)
{
	const float attributeValue = Pair.Key.GetNumericValue(AttributeSet);
	const float maxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);

	BP_OnAttributeChange(attributeValue, maxAttributeValue);
}

bool UAttributeWidget::MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
