// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnClickedResumeButton);
	QuitGameButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnClickedQuitGameButton);

}

void UPauseMenuWidget::OnClickedResumeButton()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		RemoveFromParent();
		PlayerController->SetPause(false);
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
}

void UPauseMenuWidget::OnClickedQuitGameButton()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}
}