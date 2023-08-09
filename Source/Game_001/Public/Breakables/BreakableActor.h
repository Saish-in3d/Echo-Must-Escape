// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

UCLASS() 
class GAME_001_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:
	ABreakableActor();

	virtual void Tick(float DeltaTime) override;

	void GetHit_Implementation(const FVector& ImpactPoint);

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly)
	class UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class ATreasure>> TreasureClassess;
		//class UClass* TreasureClass;

	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* BreakableCapsule;

	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* NewCapsule;


	UPROPERTY(EditDefaultsOnly)
	USceneComponent* NewSceneComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHealthPickup> HealthPickupClass;
	

	bool HasHit = false;

	UPROPERTY(EditDefaultsOnly)

	class UBoxComponent* Base;
};
