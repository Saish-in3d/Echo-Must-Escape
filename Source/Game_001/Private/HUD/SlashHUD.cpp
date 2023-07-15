// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashHUD.h"
#include "SlashOverlayWidget.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && SlashOverlayClass)
		{
			SlashOverlay = CreateWidget<USlashOverlayWidget>(Controller, SlashOverlayClass);
			if(SlashOverlay)
			{
				//UE_LOG(LogTemp, Warning, TEXT("My int32 value"));
				SlashOverlay->AddToViewport();
			}
		}
	}
}
