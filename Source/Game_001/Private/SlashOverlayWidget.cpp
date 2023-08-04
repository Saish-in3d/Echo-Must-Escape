// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashOverlayWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void USlashOverlayWidget::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void USlashOverlayWidget::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void USlashOverlayWidget::SetTimerTB(FText Text)
{
	if (Timer)
	{
		Timer->SetText(Text);
	}

}
