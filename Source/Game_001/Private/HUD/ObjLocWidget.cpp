// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ObjLocWidget.h"
#include "Components/TextBlock.h"

void UObjLocWidget::SetDistanceText(FText Text)
{

	if (DistanceText)
	{
		DistanceText->SetText(Text);
	}
}
