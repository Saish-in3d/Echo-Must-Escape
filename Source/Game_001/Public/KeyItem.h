// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/BaseItem.h"
#include "KeyItem.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API UKeyItem : public UBaseItem
{
	GENERATED_BODY()

public:
	UKeyItem();

		virtual void Use(class ABaseCharacter* Character)  override;

		bool IsKeyUsed = false;


	
};
