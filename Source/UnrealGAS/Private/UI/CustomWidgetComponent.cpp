// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CustomWidgetComponent.h"
#include "Characters/BaseCharacter.h"
#include "AbilitySystem/CustomAbilitySystemComponent.h"
#include "AbilitySystem/CustomAttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "UI/AttributeWidget.h"

// Called when the game starts
void UCustomWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilitySystemData();
	if(!IsAscInitilized())
	{
		Character->OnAscInitilized.AddDynamic(this, &ThisClass::OnAscInitilized);
		return;
	}

	InitializeAttributeDelegate();
}

void UCustomWidgetComponent::InitAbilitySystemData()
{
	Character = Cast<ABaseCharacter>(GetOwner());
	AbilitySystemComponent = Cast<UCustomAbilitySystemComponent>(Character->GetAbilitySystemComponent());
	AttributeSet = Cast<UCustomAttributeSet>(Character->GetAttributeSet());
}

bool UCustomWidgetComponent::IsAscInitilized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCustomWidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitilized)
	{
		AttributeSet->OnAttributesInitilized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UCustomWidgetComponent::OnAscInitilized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UCustomAbilitySystemComponent>(ASC);
	AttributeSet = Cast<UCustomAttributeSet>(AS);

	if(!IsAscInitilized())
	{
		return;
	}
	InitializeAttributeDelegate();
}

void UCustomWidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); //for checking the owned widget object

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			 BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UCustomWidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UAttributeWidget* AttributeWidget = Cast<UAttributeWidget>(WidgetObject);
	//We only care about Attribute Widgets
	if (!IsValid(AttributeWidget))
	{
	    return;
	}
	//Only subscribe for matching attributes
	if (!AttributeWidget->MatchesAttribute(Pair))
	{
	    return;
	}

	AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get()); //for initial values

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
	    AttributeWidget->OnAttributeChanged(Pair, AttributeSet.Get()); // For changes during the game.
	});
}