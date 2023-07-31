// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MainMenuWidget.h"
#include "MovieScene.h"
#include "LevelSequenceActor.h"
#include "LevelSequence.h"
#include "MovieSceneSequencePlayer.h"
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

				ULevelSequence* NewSequence = NewObject<ULevelSequence>( Outer,NAME_None, RF_Transactional);
				if(NewSequence)
				{
					NewSequence->MovieScene = NewObject<UMovieScene>(NewSequence, NAME_None, RF_Transactional);
					NewSequence->BindPossibles(true);
				}

				ULevelSequence* NewSequence = CreateLevelSequence("MyLevelSequence", GetTransientPackage());
				if(NewSequence)
				{
					UMovieScene* MovieScene = AddMasterMovieSceneTrack(NewSequence);
					ALevelSequenceActor* NewSequenceActor = CreateLevelSequenceActor(NewSequence, GetTransientPackage());
				}

				// Optionally, you can add more tracks, sections, and events to the MovieScene for further sequencing.

				// Play the sequence (if desired)
				if (NewSequenceActor)
				{
					NewSequenceActor->Play();
				}

			}
		}
	}



}

void AMyLevelScriptActor::Tick(float DeltaTime)
{



}
