#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon"),

};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_HitReaction UMETA(DisplayName = "HitReaction"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_Dead UMETA(DisplayName = "Dead")
};
//BlueprintReadWrite, meta = (AllowPrivateAccess = "true")
UENUM(BlueprintType)
enum class EArmState : uint8
{
	EAS_Armed,
	EAS_UnArmed
};

UENUM(BlueprintType)
enum  EDeathState 
{
	
	EDS_Death1 UMETA(DisplayName = "Death1") ,
	EDS_Death2 UMETA(DisplayName = "Death2") ,
	EDS_Death3 UMETA(DisplayName = "Death3"),
	EDS_Death4 UMETA(DisplayName = "Death4"),
	EDS_Death5 UMETA(DisplayName = "Death5"),
	EDS_Death6 UMETA(DisplayName = "Death6"),

	EDS_DeathMax UMETA(DisplayName = "DeathMax") 
	

};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_NoState UMETA(DisplayName = "NoState"),
	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged")
	
};

/*
UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
if (AnimInstance && DeathMontage)
{
	AnimInstance->Montage_Play(DeathMontage);
	FName SectionName;
	const int32 Selection = FMath::RandRange(0, 5);

	switch (Selection)
	{
	case 0:
		SectionName = FName("Death 1");
		DeathPose = EDeathState::EDS_Death6;
		break;
	case 1:
		SectionName = FName("Death 2");
		DeathPose = EDeathState::EDS_Death5;
		break;
	case 2:
		SectionName = FName("Death 3");
		DeathPose = EDeathState::EDS_Death4;
		break;
	case 3:
		SectionName = FName("Death 4");
		DeathPose = EDeathState::EDS_Death3;
		break;
	case 4:
		SectionName = FName("Death 5");
		DeathPose = EDeathState::EDS_Death2;
		break;
	case 5:
		SectionName = FName("Death 6");
		DeathPose = EDeathState::EDS_Death1;
		break;
	default:
		break;
	}

	AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
}*/
