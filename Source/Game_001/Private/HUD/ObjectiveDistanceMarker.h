// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveDistanceMarker.generated.h"

UCLASS()
class AObjectiveDistanceMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveDistanceMarker();

	// Called every frame
		virtual void Tick(float DeltaTime) override;

		FText CalculateObjDistance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	


	
	UPROPERTY(EditAnywhere)
	class UObjLocationWidgetComponent* ObjLocWidgetComp;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Base;
	

};
