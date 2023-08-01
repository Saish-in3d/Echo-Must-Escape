// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "WorldScript/MyLevelScriptActor.h"
#include "HUD/MainMenuWidget.h"

bool UMainMenuWidget::Initialize()
{
	Super::Initialize();

	StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickStartGameButton);
	ExitGame->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickExitGameButton);
	return true;
}

void UMainMenuWidget::OnClickStartGameButton()
{
	AMyLevelScriptActor* LevelScriptActor = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (LevelScriptActor)
	{
		LevelScriptActor->StartGameSequence();
		LevelScriptActor->StartClicked = true;

	}



	//fastforward and close sequence
	//remove Main mENU uI
	//Controller possess slash
	//showcheckpoint
}

void UMainMenuWidget::OnClickExitGameButton()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}
}
