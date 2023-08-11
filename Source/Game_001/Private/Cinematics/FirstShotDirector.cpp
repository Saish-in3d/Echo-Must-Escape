// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "HUD/SlashHUD.h"
#include "WorldScript/MyLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/ObjectiveDistanceMarker.h"
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

				TArray<AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveDistanceMarker::StaticClass(), FoundActors);

				for (AActor* Actor : FoundActors)
				{
					AObjectiveDistanceMarker* YourClassActor = Cast<AObjectiveDistanceMarker>(Actor);
					if (YourClassActor)
					{
						if(YourClassActor->ActorHasTag(FName("Stage1")))
						{
							YourClassActor->SetActorHiddenInGame(false);
						}
					}

				}
			}
		}
	}




}
