// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/WidgetComponent.h"
#include "CustomWidgetComponent.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class UCustomAttributeSet;
class UCustomAbilitySystemComponent;
class ABaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALGAS_API UCustomWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<ABaseCharacter> Character;
	TWeakObjectPtr<UCustomAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UCustomAttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsAscInitilized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION()
	void BindToAttributeChanges();

	UFUNCTION()
	void OnAscInitilized(UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
