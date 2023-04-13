// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MyActor.h"
#include "Treasure.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API ATreasure : public AMyActor
{
	GENERATED_BODY()
	
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:
	UPROPERTY(EditAnywhere, Category = Sounds)
	class USoundBase* CoinSound;

	class ASlashCharacter* SlashCharacter;

	UPROPERTY(EditAnywhere, Category = Money)
	int32 GoldValue;
};

