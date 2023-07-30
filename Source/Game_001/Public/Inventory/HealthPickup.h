// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MyActor.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API AHealthPickup : public AMyActor
{
	GENERATED_BODY()
	
public:

	AHealthPickup();

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	UPROPERTY(EditAnywhere)
		TSubclassOf<class UFoodItem> FoodItemClass;


};
