// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BorisPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTags/Tags.h"

void ABorisPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!IsValid(InputSubsystem))
	{
		return;
	}

	for(UInputMappingContext* Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}

	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		enhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this, &ThisClass::Primary);
		enhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this, &ThisClass::Secondary);
		enhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Started, this, &ThisClass::Tertiary);
	}
}

void ABorisPlayerController::Jump()
{
	if (!IsValid(GetCharacter()))
	{
		return;
	}

	GetCharacter()->Jump();
}

void ABorisPlayerController::StopJumping()
{
	if (!IsValid(GetCharacter()))
	{
		return;
	}

	GetCharacter()->StopJumping();
}

void ABorisPlayerController::Move(const FInputActionValue& value)
{
	if(!IsValid(GetPawn()))
	{
		return;
	}
		
	const FVector2D movementInput = value.Get<FVector2D>();

	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector forwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(forwardDirection, movementInput.Y);
	GetPawn()->AddMovementInput(rightDirection, movementInput.X);
}

void ABorisPlayerController::Look(const FInputActionValue& value)
{
	const FVector2D lookInput = value.Get<FVector2D>();

	AddYawInput(lookInput.X);
	AddPitchInput(lookInput.Y);
}

void ABorisPlayerController::Primary()
{
	ActivateAbility(Tags::AbilityTags::Primary);
}

void ABorisPlayerController::Secondary()
{
	ActivateAbility(Tags::AbilityTags::Secondary);
}

void ABorisPlayerController::Tertiary()
{
	ActivateAbility(Tags::AbilityTags::Tertiary);
}

void ABorisPlayerController::ActivateAbility(const FGameplayTag& abilityTag) const
{
	UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if(!IsValid(asc))
	{
		return;
	}
	
	asc->TryActivateAbilitiesByTag(abilityTag.GetSingleTagContainer());
}
