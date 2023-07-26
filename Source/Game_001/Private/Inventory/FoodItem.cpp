// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/FoodItem.h"
#include "Character/BaseCharacter.h"
#include "InventoryComponent.h"
#include "Character/SlashCharacter.h"
#include "Components/AttributeComponent.h"

void UFoodItem::Use(ABaseCharacter* Character)
{
	if(Character)
	{
		ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(Character);

		if (SlashCharacter)
		{
			Attributes = Character->FindComponentByClass<UAttributeComponent>();
			
			if (Attributes)
			{
				UE_LOG(LogTemp, Warning, TEXT("Eat"));
				Attributes->AddHealth(10.f);
				SlashCharacter->InitializeSlashOverlay();
			}
		}

		if (OwningInventory)
		{
			OwningInventory->RemoveItem(this);
		}
	}
}
