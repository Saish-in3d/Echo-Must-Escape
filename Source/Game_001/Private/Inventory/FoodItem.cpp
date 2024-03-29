// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/FoodItem.h"
#include "Character/BaseCharacter.h"
#include "InventoryComponent.h"
#include "Character/SlashCharacter.h"
#include "Components/AttributeComponent.h"

UFoodItem::UFoodItem()
{
	ItemDisplayName = FText::FromString("Bread");
	UseActionText = FText::FromString("Eat");
	ItemDescription = FText::FromString("Bread Increases health");

	static ConstructorHelpers::FObjectFinder<UTexture2D> ThumbnailPath(TEXT("Texture2D'/Game/Blueprints/InventorySystem/bread-icon-37168.bread-icon-37168'"));
	if (ThumbnailPath.Succeeded())
	{
		Thumbnail = ThumbnailPath.Object;
	}
}

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
				//UE_LOG(LogTemp, Warning, TEXT("Eat"));
				Attributes->AddHealth(10.f);
				 
				SlashCharacter->UpdateSlashOverlayHealth();
			}
		}

		if (OwningInventory)
		{
			OwningInventory->RemoveItem(this);
		}
	}
}
