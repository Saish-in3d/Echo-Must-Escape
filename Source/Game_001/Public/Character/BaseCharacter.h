// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "BaseCharacter.generated.h"


UCLASS()
class GAME_001_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;


	//  Combat Start
	virtual void GetHit_Implementation(const FVector& ImpactPoint);
	//  Combat End
	

	UPROPERTY(VisibleAnywhere)
		class UAttributeComponent* Attributes;

	virtual void HandleDamage(float DamageAmount);

	FORCEINLINE TEnumAsByte<EDeathState> GetDeathPose() const { return DeathPose; }

	UFUNCTION(BlueprintCallable)
		void UseItem(class UBaseItem* Item);

	FORCEINLINE void SetDoorActor(class ADoorActor* DoorActorTemp) { DoorActor = DoorActorTemp; }

	FORCEINLINE class ADoorActor* GetDoorActor() { return DoorActor; }

	void SetEquippedWeaponHidden(bool Value);


protected:
	virtual void BeginPlay() override;


	//combat start
	virtual void Attack();
	UFUNCTION()
		virtual void Die();
	UFUNCTION()
		virtual bool IsCharacterAlive();
	void DirectionalHit(const FVector& ImpactPoint);
	UFUNCTION()
		virtual void PlayHitSound(const FVector ImpactPoint);
	UFUNCTION()
		virtual void SpawnHitParticles(const FVector ImpactPoint);
	virtual int32 PlayAttackMontage();
	void PlayHitMontage(FName SectionName);
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);
	int32 PlayRandomMontageSection(const TArray<FName>Section, UAnimMontage* Montage);
	virtual int32 PlayDeathMontage();
	virtual void PlayDodgeMontage();

	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte< EDeathState > DeathPose;
	UFUNCTION()
		bool IsInTargetRange(AActor* Target, double RangeValue);
	UFUNCTION(BlueprintCallable)
		virtual	void AttackEnd();
	void DisableMeshCollision();

	UPROPERTY(EditAnywhere, Category = Combat);
	TArray<FName> AttackMontageSections;
	UPROPERTY(EditAnywhere, Category = Combat);
	TArray<FName> DeathMontageSections;
	UPROPERTY(EditAnywhere, Category = Sounds)
		USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = VFX)
		UParticleSystem* HitParticles;
	UFUNCTION(BlueprintCallable)
		virtual void DodgeEnd();
	//combat End
	

	//anim montage related start
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		class UAnimMontage* HitMontage;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		class UAnimMontage* DeathMontage;
	UPROPERTY(EditDefaultsOnly, Category = Combat)
		class UAnimMontage* DodgeMontage;
	//anim montage related End


//Weapon start
	UFUNCTION()
		virtual void EquippedWeaponDestroy();
	UFUNCTION(BlueprintCallable)
		void WeaponColliisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	UPROPERTY(VisibleAnywhere, Category = Weapon);
	class AWeapon* EquippedWeapon;
//Weapon End
//Weapon End


	//Inventory related start//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AlowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	//door

	UPROPERTY(BlueprintReadWrite)
	class ADoorActor* DoorActor;
};
