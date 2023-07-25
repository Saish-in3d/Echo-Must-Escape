// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable,EditInlineNew, DefaultToInstanced)
class GAME_001_API UBaseItem : public UObject
{
	GENERATED_BODY()

public:
	UBaseItem();
	
	UPROPERTY(Transient)
		class UWorld* World;

	/**The text for using the item. (Equip, Eat, etc)*/ 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item") 
		FText UseActionText;

	/**The mesh to display for this items pickup"*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* PickupMesh;

	/**The thumbnail for this item"*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		class UTexture2D* Thumbnail;

	/**The display name for this item in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item") 
		FText ItemDisplayName;

	/**An optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (Multiline = true)) 
		FText ItemDescription;

	UPROPERTY()
		class UInventoryComponent* OwningInventory;

	virtual void Use(class ABaseCharacter* Character) PURE_VIRTUAL(UBaseItem, )

	UFUNCTION(BlueprintImplementableEvent)
		void OnSUse( class ABaseCharacter* Character);
};
