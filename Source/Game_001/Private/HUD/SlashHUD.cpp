// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Enemy/Enemy.h"
#include "HUD/ObjectiveDistanceMarker.h"
#include "HUD/SlashHUD.h"
#include "SlashOverlayWidget.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();
	
	



}

void ASlashHUD::OnStageFC()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Stylized_Egypt_Demo"));


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
	TArray<AActor*>  LevelSequenceActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), LevelSequenceActorArray);

	for (AActor* Actor : LevelSequenceActorArray)
	{

		ALevelSequenceActor* FinalShotActorTemp = Cast<ALevelSequenceActor>(Actor);

		if (FinalShotActorTemp && FinalShotActorTemp->ActorHasTag(FName("FailShot")))
		{
			FinalShotActor = FinalShotActorTemp;
		}
	}

	if (FinalShotActor)
	{
		FinalShotActor->SequencePlayer->Play();
		EndScreenWidget = CreateWidget<UUserWidget>(GetWorld(), EndScreenWidgetClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport();
			APlayerController* Controller = GetWorld()->GetFirstPlayerController();
			if (Controller)
			{
				FInputModeUIOnly InputMode;
				Controller->SetInputMode(InputMode);
				Controller->bShowMouseCursor = true;
			}
		}
		FinalShotActor->SequencePlayer->OnFinished.AddDynamic(this, &ASlashHUD::OnStageFC);
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{


		AEnemy* EnemyTemp = Cast<AEnemy>(Actor);
		if (EnemyTemp)
		{
			EnemyTemp->Die();
			UE_LOG(LogTemp, Warning, TEXT("EnemyDead"));
		}

	}

	if (SlashOverlay)
	{
		SlashOverlay->RemoveFromViewport();
	}


	TArray<AActor*> FoundActorsM;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveDistanceMarker::StaticClass(), FoundActorsM);

	for (AActor* ActorM : FoundActorsM)
	{
		AObjectiveDistanceMarker* YourClassActor = Cast<AObjectiveDistanceMarker>(ActorM);
		if (YourClassActor)
		{
			YourClassActor->SetActorHiddenInGame(true);
		}
	}


}

void ASlashHUD::RemoveSlashOverlay()
{

	if (SlashOverlay)
	{
		SlashOverlay->RemoveFromViewport();
		GetWorldTimerManager().ClearTimer(ReverseTimerHandle);
	}
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
