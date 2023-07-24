// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Animation/HitMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/AttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/HealthBarComponent.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"
#include "Item/Weapons/Weapon.h"



AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	

	HealthBarWidgets = CreateDefaultSubobject<UHealthBarComponent>(FName("HealthBar"));

	GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnSensor"));
	PawnSensor->SightRadius = 1000.F;
	PawnSensor->SetPeripheralVisionAngle(45.f); 


}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{

	ShowHealthBar();

	if (IsCharacterAlive())
	{
		DirectionalHit(ImpactPoint);
	}
	else Die();
	PlayHitSound(ImpactPoint);

	SpawnHitParticles(ImpactPoint);

	GetWorldTimerManager().ClearTimer(PatrolTimer);

}



void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	

	if (HealthBarWidgets)
	{
		HealthBarWidgets->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		HealthBarWidgets->SetVisibility(false);

			
	}

	EnemyController = Cast<AAIController>(GetController());
	if (EnemyController && PatrolTarget)
	{
		MoveToTarget(PatrolTarget);
	}

	if (PawnSensor)
	{
		PawnSensor->OnSeePawn.AddDynamic(this, &AEnemy::AfterPawnSeen);
	}

	UWorld* World = GetWorld();

	if (World && WeaponClass)
	{
		class AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		DefaultWeapon->Equip(GetMesh(), FName("RightHandSocket"), this);
		DefaultWeapon->SetOwner(this);
		EquippedWeapon = DefaultWeapon;
	}
	Tags.Add(FName("Enemy"));

}





AActor* AEnemy::ChoosePatrolTarget()
{
	if (PatrolTarget && EnemyController && &PatrolTargets)
	{
		TArray<AActor*> ValidTargets;
		for (AActor* Target : PatrolTargets)
		{
			if (Target != PatrolTarget)
			{
				ValidTargets.AddUnique(Target);
			}
		}
		const int32 NumPatrolTargets = ValidTargets.Num();

		if (NumPatrolTargets > 0)
		{
			const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
			AActor* Target = ValidTargets[TargetSelection];
			PatrolTarget = Target;
			return PatrolTarget;
			//PatrolTarget = PatrolTargets[TargetSelection];
		}
		
	}
	return nullptr;
}

void AEnemy::CheckMovePatrolTarget()
{
	if (IsInTargetRange(PatrolTarget, Range))
	{
		UE_LOG(LogTemp, Warning, TEXT("Reached Target!"));
		PatrolTarget = ChoosePatrolTarget();
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimeFinished, 5.f); //PatrolTimeFinsihed
		//delay
	}
}

void AEnemy::PatrolTimeFinished()
{
	MoveToTarget(PatrolTarget);
	GetCharacterMovement()->MaxWalkSpeed = PatrollingSpeed;
}

void AEnemy::MoveToTarget(AActor* Target)
{
	
	FAIMoveRequest MoveRequest;
	MoveRequest.SetAcceptanceRadius(12.f);
	MoveRequest.SetGoalActor(Target);
	EnemyController->MoveTo(MoveRequest);
}

void AEnemy::AfterPawnSeen(APawn* SeenPawn) 
{
	if (EnemyState == EEnemyState::EES_Chasing) { return; }
	const bool bShouldChaseTarget =
		SeenPawn->ActorHasTag(FName("EngageableTarget")) &&
		EnemyState != EEnemyState::EES_Attacking &&
		EnemyState != EEnemyState::EES_Dead &&
		EnemyState < EEnemyState::EES_Chasing;

	if (bShouldChaseTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn Seen!"));
		GetWorldTimerManager().ClearTimer(PatrolTimer);
		if(!SeenPawn->ActorHasTag(FName("Dead")))
		{
			CombatTarget = SeenPawn;
			if (IsInTargetRange(CombatTarget, 500))
			{
				StartChasingTarget();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT(" Combat Target out of range"));
			}
		}
	}
}

void AEnemy::HideHealthBar()
{
	if (HealthBarWidgets)
	{
		HealthBarWidgets->SetVisibility(false);
	}
}

void AEnemy::ShowHealthBar()
{
	if (HealthBarWidgets)
	{
		HealthBarWidgets->SetVisibility(true);
	}
}

void AEnemy::LoseInterest()
{
	CombatTarget = nullptr;
	HideHealthBar();
}

void AEnemy::StartPatrollling()
{
	EnemyState = EEnemyState::EES_Patrolling;
	GetCharacterMovement()->MaxWalkSpeed = PatrollingSpeed;
	MoveToTarget(PatrolTarget);
}

void AEnemy::StartChasingTarget()
{
	if (CombatTarget)
	{
		EnemyState = EEnemyState::EES_Chasing;
		MoveToTarget(CombatTarget);
		GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;
		UE_LOG(LogTemp, Warning, TEXT(" started chasing again"));
	}
}

void AEnemy::AttackEnd()
{
	EnemyState = EEnemyState::EES_NoState;
	CheckCombatTarget();
	UE_LOG(LogTemp, Warning, TEXT(" DisEngaged "));
	//StartPatrollling();
}

void AEnemy::StartAttackTimer()
{
	UE_LOG(LogTemp, Warning, TEXT(" Attacking"));
	EnemyState = EEnemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(AttackMin, AttackMax);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack ,AttackTime);
}

void AEnemy::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyState == EEnemyState::EES_Dead) { return; }
	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	else
	{
		CheckMovePatrolTarget();
	}
	
	//if enemy state = attacking & is not in 200 attacking range
	//
	
	

}

void AEnemy::CheckCombatTarget()
{
	if (CombatTarget)
	{
		//const double Distance = (CombatTarget->GetActorLocation() - GetActorLocation()).Size();
		if (!IsInTargetRange(CombatTarget, DistanceLimit) )
		{
			ClearAttackTimer();
			LoseInterest();
			if (EnemyState != EEnemyState::EES_Engaged)
			{
				StartPatrollling();
			}
			UE_LOG(LogTemp, Warning, TEXT(" distance too long enemy lost intrest"));
		}

		else if (IsInTargetRange(CombatTarget, 200.f) && EnemyState != EEnemyState::EES_Attacking && EnemyState != EEnemyState::EES_Dead && EnemyState != EEnemyState::EES_Engaged)
		{
			//ClearAttackTimer();
			StartAttackTimer();
		}

		else if (!IsInTargetRange(CombatTarget, 200.f) && EnemyState != EEnemyState::EES_Chasing)
		{
			ClearAttackTimer();
			StartChasingTarget();
		}
		

	}
	else
	{
		StartPatrollling();
	}
}



float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	
	CombatTarget = EventInstigator->GetPawn();
	StartChasingTarget();
	UE_LOG(LogTemp, Warning, TEXT("Enemy hit chase!"));
	return DamageAmount;
}

void AEnemy::HandleDamage(float DamageAmount)
{
	Super::HandleDamage(DamageAmount);
	if (Attributes && HealthBarWidgets)
	{

		HealthBarWidgets->SetHealthPercent(Attributes->GetHealthPercent());  // health pc = Health/MaxHealth
	}

}

FVector AEnemy::GetTranslationWarpTarget()
{
	if(CombatTarget == nullptr) return FVector();

	const FVector CombatTargetLoaction = CombatTarget->GetActorLocation();
	const FVector Location = GetActorLocation();

	FVector TargetToMe = (Location - CombatTargetLoaction).GetSafeNormal();
	TargetToMe *= WarpTargetDistance;

	return CombatTargetLoaction + TargetToMe;

	
}

FVector AEnemy::GetRotationWarpTarget()
{
	if (CombatTarget)
	{
		return CombatTarget->GetActorLocation();
	}
	return FVector();
}

void AEnemy::Die()
{
	EnemyState = EEnemyState::EES_Dead;
	ClearAttackTimer();
	//PlayDeathMontage();
	EquippedWeaponDestroy();
	HideHealthBar();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(5.f);
}

void AEnemy::EquippedWeaponDestroy()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}
}

void AEnemy::Attack()
{
	if (CombatTarget && CombatTarget->ActorHasTag(FName("Dead")))
	{
		CombatTarget = nullptr;
	}
	if (CombatTarget == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT(" Engaged "));
	EnemyState = EEnemyState::EES_Engaged;
	PlayAttackMontage();
	
}


