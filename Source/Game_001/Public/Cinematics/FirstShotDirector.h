// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceDirector.h"
#include "FirstShotDirector.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API UFirstShotDirector : public ULevelSequenceDirector
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void EndFirstShot();
	
};
