// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MainMenuWidget.h"
#include "MovieScene.h"
//#include "LevelSequenceActor.h"
//#include "LevelSequence.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/ObjectiveDistanceMarker.h"
#include "MovieSceneSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"


#include "LevelSequence/Public/LevelSequence.h"
#include "WorldScript/MyLevelScriptActor.h"

void AMyLevelScriptActor::BeginPlay()
{

	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && MainMenuWidgetClass)
		{
			MainMenuWidget = CreateWidget<UMainMenuWidget>(Controller, MainMenuWidgetClass);
			if (MainMenuWidget)
			{
				//UE_LOG(LogTemp, Warning, TEXT("My int32 value"));
				MainMenuWidget->AddToViewport();

				FInputModeUIOnly InputMode ;
				Controller->SetInputMode(InputMode);
				Controller->bShowMouseCursor = true;

				TArray<AActor*>  LevelSequenceActorArray;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), LevelSequenceActorArray);

				for (AActor* Actor : LevelSequenceActorArray)
				{
					ALevelSequenceActor* FirstShotActorTemp = Cast<ALevelSequenceActor>(Actor);

					if (FirstShotActorTemp && FirstShotActorTemp->ActorHasTag(FName("FirstShot")))
					{
						FirstShotActor = FirstShotActorTemp;
					}
				}

				if (FirstShotActor)
				{
					FirstShotActor->SequencePlayer->PlayLooping();
				}
			}
		}

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(World, AObjectiveDistanceMarker::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors)
		{
			AObjectiveDistanceMarker* YourClassActor = Cast<AObjectiveDistanceMarker>(Actor);
			if (YourClassActor)
			{
				YourClassActor->SetActorHiddenInGame(true);
			}

		}
	}



}

void AMyLevelScriptActor::Tick(float DeltaTime)
{



}

void AMyLevelScriptActor::StartGameSequence()
{
	if (FirstShotActor && MainMenuWidget)
	{


		FirstShotActor->SequencePlayer->SetPlayRate(10.f);

		//FirstShotActor->SequencePlayer->Play();

	}
}

void AMyLevelScriptActor::RemoveMainMenu()
{
	if(MainMenuWidget)
	{
		MainMenuWidget->RemoveFromViewport();
	}

}

void AMyLevelScriptActor::SetGameInput()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}

}

void AMyLevelScriptActor::StopSequence()
{
	if (FirstShotActor)
	{


		FirstShotActor->SequencePlayer->Stop();

		

	}

}


