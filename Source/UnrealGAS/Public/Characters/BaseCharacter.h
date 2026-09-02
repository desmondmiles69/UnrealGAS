// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FOnAttributeChangeData;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class USpringArmComponent;
class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitilized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class UNREALGAS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; }

	bool GetIsAlive() { return bAlive; }
	void SetIsAlive(bool bAliveStatus) { bAlive = bAliveStatus; }

	UPROPERTY(BlueprintAssignable)
	FASCInitilized OnAscInitilized;

	UFUNCTION(BlueprintCallable, Category = "Character|Death")
	virtual void HandleRespawn();
	
	UFUNCTION(BlueprintCallable)
	virtual void ResetAttributes();
	 
protected:
	virtual void GiveStartupAbilities();
	virtual void InitilizeAttributes() const;


	void OnHealthChanged(const FOnAttributeChangeData& ArrtibuteChangeData);
	virtual void HandleDeath();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> InitilizeAttributesEffect;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> ResetAttributesEffect;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
	bool bAlive;
};