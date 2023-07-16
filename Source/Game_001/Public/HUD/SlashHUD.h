// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlashHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAME_001_API ASlashHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = Slash)
		TSubclassOf< class USlashOverlayWidget> SlashOverlayClass;

	UPROPERTY()
		class USlashOverlayWidget* SlashOverlay;

public:
	FORCEINLINE class USlashOverlayWidget* GetSlashOverlay() const { return SlashOverlay; }
	
};
