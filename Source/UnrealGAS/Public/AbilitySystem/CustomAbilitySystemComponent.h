// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CustomAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALGAS_API UCustomAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
 
public:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(BlueprintCallable)
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level);

	UFUNCTION(BlueprintCallable)
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level = 1);

private:
	void HandleAutoActivatedAbility(const FGameplayAbilitySpec& abilitySpec);
};
