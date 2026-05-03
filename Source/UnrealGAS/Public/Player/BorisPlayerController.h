// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BorisPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class UNREALGAS_API ABorisPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs|Movement")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs|Movement")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs|Movement")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs|Abilities")
	TObjectPtr<UInputAction> SecondaryAction;

	UPROPERTY(EditDefaultsOnly, Category="Inputs|Abilities")
	TObjectPtr<UInputAction> TertiaryAction;

	void Jump();
	void StopJumping();

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);

	void Primary();
	void Secondary();
	void Tertiary();

	void ActivateAbility(const FGameplayTag& abilityTag) const;
};
