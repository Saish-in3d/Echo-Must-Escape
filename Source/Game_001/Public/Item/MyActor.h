// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Character/SlashCharacter.h"
#include "MyActor.generated.h"

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped,
};


UCLASS()
class GAME_001_API AMyActor : public AActor  // api provides special data for reflection  (which helps for better code before compilatrion)
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	

	virtual void Tick(float DeltaTime) override;

	EItemState ItemState = EItemState::EIS_Hovering;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* ItemMesh;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



protected:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere;


private:
	UPROPERTY(VisibleAnywhere)
	class ASlashCharacter* SlashCharacter = nullptr;


};
