// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
#include "Character/BaseCharacter.h"
#include "Interfaces/HitInterface.h"
#include "Character/CharacterTypes.h"
#include "Enemy.generated.h"

UCLASS()
class GAME_001_API AEnemy : public ABaseCharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	// AI Combat Start
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// AI Combat End
	
protected:
	virtual void BeginPlay() override;


	//Navigation start
	UFUNCTION()
		AActor* ChoosePatrolTarget();
	UFUNCTION()
		void PatrolTimeFinished();
	UFUNCTION()
		void MoveToTarget(AActor* Target);
	UFUNCTION()
		void AfterPawnSeen(APawn* SeenPawn);
	void LoseInterest();
	void StartPatrollling();
	void StartChasingTarget();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		AActor* PatrolTarget;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		TArray<AActor*>PatrolTargets;
	UPROPERTY(EditAnywhere, Category = Combat)
		float PatrollingSpeed = 125.f;
	UPROPERTY(EditAnywhere, Category = Combat)
		float ChasingSpeed = 300.f;
	UPROPERTY()
		class AAIController* EnemyController;
	UPROPERTY(BlueprintReadOnly)
		EEnemyState EnemyState = EEnemyState::EES_Patrolling;
	UPROPERTY()
		double Range = 300.f;
	UPROPERTY()
		FTimerHandle PatrolTimer;
	UPROPERTY(VisibleAnywhere)
		class UPawnSensingComponent* PawnSensor;
	//Navigation end

	//Combat Start
	void HideHealthBar();
	void ShowHealthBar();
	virtual void AttackEnd() override;
	void StartAttackTimer();
	void ClearAttackTimer();
	virtual int32 PlayDeathMontage() override;

	UPROPERTY(BlueprintReadOnly, Category = Combat)
		 AActor* CombatTarget;

	UPROPERTY()
		FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, Category = Combat)
		float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category = Combat)
		float AttackMax = 1.f;
	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte< EDeathState > DeathPose;
	//Combat End


private:
	  // AI Navigation Start 
	UFUNCTION()
		void CheckMovePatrolTarget();
		void CheckCombatTarget();


		UPROPERTY()
			double DistanceLimit = 500.f;
		// AI Navigation Start 

		//Combat Start 
		virtual void Die() override;
		virtual void EquippedWeaponDestroy() override;
		virtual void Attack() override;

		UPROPERTY(VisibleAnywhere)
			class UHealthBarComponent* HealthBarWidgets;
		UPROPERTY(EditAnywhere)
			TSubclassOf<class AWeapon>WeaponClass;

		//Combat End

};
