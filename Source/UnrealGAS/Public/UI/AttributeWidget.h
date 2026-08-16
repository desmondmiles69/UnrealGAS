// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystem/CustomAttributeSet.h"
#include "AttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAS_API UAttributeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributesWidget")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributesWidget") 
	FGameplayAttribute MaxAttribute;

	void OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UAttributeSet* AttributeSet);
	bool MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float newValue, float newMaxValue);
};
