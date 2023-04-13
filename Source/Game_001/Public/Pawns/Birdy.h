// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Birdy.generated.h"

UCLASS()
class GAME_001_API ABirdy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere);
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere);
	class USkeletalMeshComponent* BirdMesh;

private:
	UPROPERTY(VisibleAnywhere);
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere);
	class UCameraComponent* ViewCamera;




	

};
