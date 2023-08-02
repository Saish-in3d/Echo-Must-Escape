// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "HUD/SlashHUD.h"
#include "WorldScript/MyLevelScriptActor.h"
#include "Cinematics/FirstShotDirector.h"

void UFirstShotDirector::EndFirstShot()
{

	AMyLevelScriptActor* LevelScriptActor = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (LevelScriptActor && LevelScriptActor->StartClicked == true)
	{
		LevelScriptActor->StopSequence();
		LevelScriptActor->SetGameInput();
		LevelScriptActor->RemoveMainMenu();

		APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());
			if (SlashHUD)
			{
				SlashHUD->InitSlashOverlay();
			}
		}
	}




}
