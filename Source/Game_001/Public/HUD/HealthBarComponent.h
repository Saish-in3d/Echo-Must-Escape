// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void SetHealthPercent(float percent);
	
private:
	UPROPERTY()
		class UHealthBar* HealthBarWidget;
	
};
