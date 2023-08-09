// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"
 
UCLASS()
class GAME_001_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();

	void AddKeyToDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DoorOverlap;

	UPROPERTY(EditAnywhere)
		class USceneComponent* Base;

	UPROPERTY(EditAnywhere)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY()
	int64 SubmittedKeys = 0;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FQuat StartRotation;

	FQuat EndRotation;

	float Alpha = 0.f;

	

};
