// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Inventory/FoodItem.h"
#include "InventoryComponent.h"
#include "Character/SlashCharacter.h"
#include "Inventory/HealthPickup.h"

AHealthPickup::AHealthPickup()
{
}

void AHealthPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(FName("Slash")))
	{
		ASlashCharacter* SlashChar = Cast<ASlashCharacter>(OtherActor);

		if (SlashChar)
		{

			UInventoryComponent* Inventory = SlashChar->FindComponentByClass<UInventoryComponent>();
			UFoodItem* KeyItemObject = NewObject< UFoodItem>(UFoodItem::StaticClass());

			if (Inventory && KeyItemObject && Inventory->Items.Num() <= Inventory->Capacity - 1)
			{

				Inventory->AddItem(KeyItemObject);
				Destroy();
			}
		}


	}


}
