// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjLocationWidgetComponent.h"
#include "HUD/ObjLocWidget.h"
#include "HUD/ObjectiveDistanceMarker.h"



void UObjLocationWidgetComponent::SetDistanceText()
{
	if (ObjLocWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("DIST"));

		ObjLocWidget = Cast<UObjLocWidget>(GetUserWidgetObject());
	}

	if (ObjectiveDistanceMarker == nullptr)
	{

		ObjectiveDistanceMarker = Cast<AObjectiveDistanceMarker>(GetOwner());
	}
	
	if (ObjLocWidget) //&& ObjectiveDistanceMarker
	{
		

		//ObjectiveDistanceMarker->CalculateObjDistance()
		ObjLocWidget->SetDistanceText(ObjectiveDistanceMarker->CalculateObjDistance());


	}
}
