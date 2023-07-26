// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_001_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();



	int32 Capacity;

	bool AddItem(class UBaseItem* Item);

	bool AddSubClassItem(class TSubclassOf< UBaseItem>*  Item);

	//bool AddItem(TSubclassOf<class UBaseItem> Item);

	bool RemoveItem(class UBaseItem* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UBaseItem*> DefaultItems;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<class UBaseItem*> Items;





		




protected:
	// Called when the game starts
	virtual void BeginPlay() override;



		

};
