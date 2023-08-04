// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ObjLocationWidgetComponent.generated.h"

/** 
 *  
 */
UCLASS()
class GAME_001_API UObjLocationWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()


public:
	void SetDistanceText();


private:

	class UObjLocWidget* ObjLocWidget;

	class AObjectiveDistanceMarker* ObjectiveDistanceMarker;
	
};
