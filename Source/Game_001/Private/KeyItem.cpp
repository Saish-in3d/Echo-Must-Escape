// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/ConstructorHelpers.h"
#include "InventoryComponent.h"
#include "Character/SlashCharacter.h"
#include "Door/DoorActor.h"
#include "KeyItem.h"

UKeyItem::UKeyItem()
{
	ItemDisplayName = FText::FromString("Door Key");
	UseActionText = FText::FromString("Use");
	ItemDescription = FText::FromString("A Single key or multiple keys are used to open the gate"); 	


	static ConstructorHelpers::FObjectFinder<UTexture2D> ThumbnailPath(TEXT("Texture2D'/Game/Blueprints/InventorySystem/key-png-32737__1_.key-png-32737__1_'"));
	if (ThumbnailPath.Succeeded())
	{
		Thumbnail = ThumbnailPath.Object;
	}

}

void UKeyItem::Use(ABaseCharacter* Character)
{
	if (Character)
	{
		ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(Character);

		if (SlashCharacter)
		{
			ADoorActor* DoorActor = SlashCharacter->GetDoorActor();
			if (DoorActor)

			{
				
				if (OwningInventory && IsKeyUsed == false)
				{
					DoorActor->AddKeyToDoor();
					UE_LOG(LogTemp, Warning, TEXT(" Removed Key1"));
					OwningInventory->RemoveItem(this);
				}
				
			}
		}



	}
	//Door->SubmitKey()
	//+1 key in door
	//if door keys is equal to to required keys
	//door opens
}
