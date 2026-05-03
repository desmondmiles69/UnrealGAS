// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BorisPlayerState.generated.h"

class UAbilitySystemComponent;

UCLASS()
class UNREALGAS_API ABorisPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	ABorisPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
