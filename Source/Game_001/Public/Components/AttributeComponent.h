// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) 
class GAME_001_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
		float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
		float MaxHealth = 100.f;

	// Current Stamina
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
		float Stamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
		float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
		float DodgeCost = 14.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
		float StaminaRegenRate = 8.f;
	
public:
	UFUNCTION()
	void RecieveDamage(float Damage);
	
	UFUNCTION()
		float GetHealthPercent();

	UFUNCTION()
		bool IsAlive();

	void RegenStamina(float DeltaTime);

	void UseStamina(float StaminaCost);

	float GetStaminaPercent();

	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	FORCEINLINE float GetStamina() const { return Stamina; }

	void AddHealth(float AddHealth);

};
