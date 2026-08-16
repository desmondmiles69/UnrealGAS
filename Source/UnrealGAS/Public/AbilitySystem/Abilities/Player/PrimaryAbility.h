// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "PrimaryAbility.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAS_API UPrimaryAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="PrimaryAbility")
	TArray<AActor*> HitboxOverlapTest();

	UFUNCTION(BlueprintCallable, Category = "PrimaryAbility")
	void SendHitEventToActor(TArray<AActor*> HitActors);

private:
	void DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	float HitBoxRadius = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	float HitBoxForwardOffset = 200.f;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	float HitBoxElevationOffset = 20.f;
};
