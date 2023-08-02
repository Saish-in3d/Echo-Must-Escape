// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlashOverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API USlashOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealthBarPercent(float Percent);
	void SetStaminaBarPercent(float Percent);

	void SetTimerTB(FText Text);

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* StaminaProgressBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Timer;


	
};
