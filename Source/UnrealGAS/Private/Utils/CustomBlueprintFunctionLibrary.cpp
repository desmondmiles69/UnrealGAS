// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/CustomBlueprintFunctionLibrary.h"

EHitDirection UCustomBlueprintFunctionLibrary::GetHitDirection(const FVector& forward, const FVector& toInstigator)
{
	const float dot = FVector::DotProduct(forward, toInstigator);

	if (dot < -0.5)
	{
		return EHitDirection::Back;
	}

	if (dot < 0.5)
	{
		const FVector cross = FVector::CrossProduct(forward, toInstigator);
		if (cross.Z < 0.0f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}

	return EHitDirection::Forward;
}

FName UCustomBlueprintFunctionLibrary::GetHitDirectionName(const EHitDirection& hitDirection)
{
	switch(hitDirection)
	{
		case EHitDirection::Back: return FName("Back");
		case EHitDirection::Forward: return FName("Forward");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Left: return FName("Left");
		default: return FName("None");
	}
}
