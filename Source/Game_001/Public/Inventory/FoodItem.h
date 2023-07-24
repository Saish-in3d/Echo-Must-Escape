// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/BaseItem.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API UFoodItem : public UBaseItem
{
	GENERATED_BODY()

protected:

	virtual void Use(class ABaseCharacter* Character)  override;

	UPROPERTY(VisibleAnywhere)
		class UAttributeComponent* Attributes;
	
};
