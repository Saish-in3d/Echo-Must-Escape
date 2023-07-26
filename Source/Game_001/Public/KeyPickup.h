// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MyActor.h"
#include "KeyPickup.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API AKeyPickup : public AMyActor
{
	GENERATED_BODY()
	
public:
	AKeyPickup();
	

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	UPROPERTY(EditAnywhere, Category = Sounds)
		class USoundBase* CoinSound;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UKeyItem> KeyItemClass;
};
