// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashHUD.h"
#include "SlashOverlayWidget.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();
	
	



}

void ASlashHUD::InitSlashOverlay()
{

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && SlashOverlayClass)
		{
			SlashOverlay = CreateWidget<USlashOverlayWidget>(Controller, SlashOverlayClass);
			if (SlashOverlay)
			{
				//UE_LOG(LogTemp, Warning, TEXT("My int32 value"));
				SlashOverlay->AddToViewport();

				GetWorld()->GetTimerManager().SetTimer(ReverseTimerHandle, this, &ASlashHUD::ReverseTimerExpired, Duration, false);



				

			}
		}
	}
}

void ASlashHUD::ReverseTimerExpired()
{


}

void ASlashHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(SlashOverlay)
	{
		float TimeLeft = GetWorld()->GetTimerManager().GetTimerRemaining(ReverseTimerHandle);

		//UE_LOG(LogTemp, Warning, TEXT("Your Float Value: %f"), TimeLeft);

		int32 IntegerValue = FMath::FloorToInt(TimeLeft);
		FText DisplayText = FText::AsNumber(IntegerValue);
		SlashOverlay->SetTimerTB(DisplayText);
	}

}
