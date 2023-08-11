// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Character/CharacterTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"


UCLASS()
class GAME_001_API ATriggerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATriggerActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)

		class UBoxComponent* Base;


	UPROPERTY(EditInstanceOnly)

		class UBoxComponent* EntryOverlap;

	UFUNCTION()
		virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PerformStage2(AActor* OtherActor, bool& retflag);

	void PerformStage1(AActor* OtherActor);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
		class ALevelSequenceActor* MidShotActor;


	UFUNCTION()
		void OnStage1C();

	UFUNCTION()
		void OnStage2C();

	class ASlashCharacter* SlashChar;

	UPROPERTY(EditInstanceOnly)
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditInstanceOnly)
		FTransform ArrowTransform;

	UPROPERTY()
	EGameStage GameStage = EGameStage::EGS_NoState;

	UPROPERTY()
		class ALevelSequenceActor* FinalShotActor;
};
