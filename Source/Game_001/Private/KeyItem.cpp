// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"

UKeyItem::UKeyItem()
{
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void UKeyItem::Use(ABaseCharacter* Character)
{

}
