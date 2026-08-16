// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "HitReactAbility.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAS_API UHitReactAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "EnemyAbility")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "EnemyAbility")
	FVector ActorForward;

	UPROPERTY(BlueprintReadOnly, Category = "EnemyAbility")
	FVector ToInstigator;
};
