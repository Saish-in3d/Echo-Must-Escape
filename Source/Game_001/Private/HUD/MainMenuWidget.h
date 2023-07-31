// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:


	virtual bool Initialize();


	UPROPERTY(meta = (BindWidget))
		class UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitGame;

private:
	UFUNCTION()
		void OnClickStartGameButton();
	UFUNCTION()
		void OnClickExitGameButton();

	
};
