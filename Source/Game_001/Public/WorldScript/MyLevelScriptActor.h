// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;



private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;


	class UMainMenuWidget* MainMenuWidget;

};
