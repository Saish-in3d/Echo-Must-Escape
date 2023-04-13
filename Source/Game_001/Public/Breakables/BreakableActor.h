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
	UPROPERTY(VisibleAnywhere)
	class UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class ATreasure>> TreasureClassess;
		//class UClass* TreasureClass;

	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* BreakableCapsule;

	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* NewCapsule;


	UPROPERTY(VisibleAnywhere)
		USceneComponent* NewSceneComponent;
	

	bool HasHit = false;
};
