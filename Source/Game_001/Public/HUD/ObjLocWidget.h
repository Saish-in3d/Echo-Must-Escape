// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjLocWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API UObjLocWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetDistanceText(FText Text);
	

private:
		UPROPERTY(meta = (BindWidget))
		class UTextBlock* DistanceText;


	
};
