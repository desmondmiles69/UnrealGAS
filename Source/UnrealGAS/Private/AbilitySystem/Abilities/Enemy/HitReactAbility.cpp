// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Enemy/HitReactAbility.h"

void UHitReactAbility::CacheHitDirectionVectors(AActor* Instigator)
{
	ActorForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();

	const FVector AvatorLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();

	ToInstigator = InstigatorLocation - AvatorLocation;
	ToInstigator.Normalize();
}
