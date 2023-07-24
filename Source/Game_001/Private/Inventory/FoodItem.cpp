// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/FoodItem.h"
#include "Character/BaseCharacter.h"
#include "Components/AttributeComponent.h"

void UFoodItem::Use(ABaseCharacter* Character)
{
	Attributes = Character->FindComponentByClass<UAttributeComponent>();

	if (Attributes)
	{
		Attributes->AddHealth(50.f);
	}
}
