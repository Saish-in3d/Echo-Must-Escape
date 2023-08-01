// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
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

	}




}
