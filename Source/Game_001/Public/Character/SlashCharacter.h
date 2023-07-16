// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interfaces/HitInterface.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"


class AMyActor;



UCLASS()
class GAME_001_API ASlashCharacter : public ABaseCharacter, public IHitInterface
{
	GENERATED_BODY()


public:
	ASlashCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	FORCEINLINE void SetOverlappingActor(AMyActor* Actorr) { OverlappingActorr = Actorr; }
	FORCEINLINE ECharacterState GetCharacterState() { return CharacterState; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Jump() override;

	FORCEINLINE EActionState GetActionState() const { return ActionState; }
protected:
	virtual void BeginPlay() override;


	/* Input functions Start */
	void MoveForward(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void MoveRight(float Value);
	void Equip_E();
	virtual void Attack() override;
	/* Input functions End */

	/** Combat Start */
	virtual void AttackEnd() override;
	bool CanDisarm();
	bool CanArm();
	void PlayEquipMontage(FName SectionName);
	UFUNCTION(BlueprintCallable)
	void Disarm();
	UFUNCTION(BlueprintCallable)
	void Arm();
	UFUNCTION(BlueprintCallable)
	void ReactEnd();
	virtual void Die() override;
	/** Combat End */


private:

	void InitializeSlashOverlay();

	bool IsUnoccupied();

	void SetHUDHealth();

	//Char Component Start
	UPROPERTY(VisibleAnywhere);
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere);
	class UCameraComponent* ViewCamera;
	UPROPERTY(VisibleAnywhere, Category = Hair);
	class UGroomComponent* Hair;
	UPROPERTY(VisibleAnywhere, Category = Hair);
	class UGroomComponent* Eyebrows;
	//Char Component End


	//Weapon Start
	UPROPERTY(VisibleInstanceOnly, Category = info);
	class AMyActor* OverlappingActorr = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	class UAnimMontage* EquipMontage;
	//Weapon End


	// Char State start
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EActionState ActionState = EActionState::EAS_Unoccupied ;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	EArmState ArmState = EArmState::EAS_UnArmed;
	// Char State End

	UPROPERTY()
	class USlashOverlayWidget* SlashOverlay;


};
