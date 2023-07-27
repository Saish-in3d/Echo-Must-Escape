// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "KeyItem.h"
#include "InventoryComponent.h"
#include "Character/SlashCharacter.h"
#include "KeyPickup.h"

AKeyPickup::AKeyPickup()
{
}

void AKeyPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//iNVENTORY ADD ITEM

	if (OtherActor)
	{
		ASlashCharacter* SlashChar = Cast<ASlashCharacter>(OtherActor);
		
		if (SlashChar)
		{
			
			UInventoryComponent* Inventory = SlashChar->FindComponentByClass<UInventoryComponent>();
			//TSubclassOf< UKeyItem>* KeyItemObject = NewObject<TSubclassOf< UKeyItem>>();
			UKeyItem* KeyItemObject = NewObject< UKeyItem>(UKeyItem::StaticClass());
			//KeyItemClass* KeyItemObject = GetWorld()->SpawnActor<KeyItemClass>(KeyItemClass::StaticClass());
			UClass* MyBpClass = FindObject<UClass>(nullptr, TEXT("MyPackage.MyBpClass_C"), true);


			if (Inventory && KeyItemObject)
			{
				
				Inventory->AddItem(KeyItemObject);
			}
		}

		if (CoinSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				CoinSound,
				GetActorLocation()
			);
		}
		Destroy();
	}
}
	
	


