// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MyActor.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API AWeapon : public AMyActor
{
	GENERATED_BODY()

		
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ExecuteGetHit(FHitResult& BoxHit);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SwordBox;


	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;

	UFUNCTION(BlueprintImplementableEvent)
		void CreateField(const FVector& ImpactPoint);


public:
	//void Equip(USceneComponent* InParent, FName InSocketName);
	AWeapon();

	void Equip(USceneComponent* InParent, FName InSocketName, APawn* Instigatorr);

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	FORCEINLINE UBoxComponent* GetSwordBox() { return SwordBox; }

	TArray<AActor*> IgnoreActors;

	UPROPERTY(EditAnywhere)
		float Damage = 21.f;


private:

	void BoxTrace(FHitResult &BoxHit);

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceExtent = FVector(5.f);
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bShowBoxDebug = false;

	AActor* WeaponOwner ;

};

