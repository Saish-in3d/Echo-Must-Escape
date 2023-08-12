// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SlashCharacter.h"
#include "Components/ArrowComponent.h" 
#include "GameFramework/CharacterMovementComponent.h" 


#include "HUD/ObjectiveDistanceMarker.h"

#include "Components/BoxComponent.h"


// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UBoxComponent>(FName("BaseComponent"));
	if (Base)
	{
		SetRootComponent(Base);
	}
	EntryOverlap = CreateDefaultSubobject<UBoxComponent>(FName("DoorOverlap"));
	EntryOverlap->SetupAttachment(Base);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent")); 
	if (ArrowComponent)
	{
		
		ArrowComponent->SetupAttachment(Base);
		ArrowComponent->SetRelativeTransform(ArrowTransform);
	}

}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();



	EntryOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATriggerActor::OnBoxOverlap);

	EntryOverlap->OnComponentEndOverlap.AddDynamic(this, &ATriggerActor::OnBoxEndOverlap);
	
}

void ATriggerActor::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SlashChar = Cast<ASlashCharacter>(OtherActor);
	if (SlashChar && SlashChar->SlashGameStage == EGameStage::EGS_NoState)
	{
		PerformStage1(OtherActor);
	}
	if (SlashChar && SlashChar->SlashGameStage == EGameStage::EGS_Stage1C)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slash Triggered"));
		bool retflag;
		PerformStage2(OtherActor, retflag);
		if (retflag) return;

	}

}

void ATriggerActor::PerformStage2(AActor* OtherActor, bool& retflag)
{
	retflag = true;
	if (OtherActor->ActorHasTag(FName("Stage2C"))) { return; }
	SlashChar = Cast<ASlashCharacter>(OtherActor);
	if (SlashChar)
	{
		

		SlashChar->SetEquippedWeaponHidden(true);

		SlashChar->Tags.Add(FName("Stage2C"));

		TArray<AActor*>  LevelSequenceActorArray;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), LevelSequenceActorArray);

		for (AActor* Actor : LevelSequenceActorArray)
		{

			ALevelSequenceActor* FinalShotActorTemp = Cast<ALevelSequenceActor>(Actor);

			if (FinalShotActorTemp && FinalShotActorTemp->ActorHasTag(FName("FinalShot")))
			{
				FinalShotActor = FinalShotActorTemp;
			}
		}

		if (FinalShotActor)
		{
			FinalShotActor->SequencePlayer->Play();
			FinalShotActor->SequencePlayer->OnFinished.AddDynamic(this, &ATriggerActor::OnStage2C);
		}

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveDistanceMarker::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors)
		{
			AObjectiveDistanceMarker* YourClassActor = Cast<AObjectiveDistanceMarker>(Actor);
			if (YourClassActor)
			{
				if (YourClassActor->ActorHasTag(FName("Stage2")))
				{
					YourClassActor->SetActorHiddenInGame(true);
				}
			}

		}

		if (EntryOverlap)
		{
			EntryOverlap->SetGenerateOverlapEvents(false);
		}
	}

	
	retflag = false;
}

void ATriggerActor::PerformStage1(AActor* OtherActor)
{
	
	if (OtherActor->ActorHasTag(FName("Stage1C"))) { return; }
	SlashChar = Cast<ASlashCharacter>(OtherActor);
	if (SlashChar)
	{
		SlashChar->SetEquippedWeaponHidden(true);

		SlashChar->Tags.Add(FName("Stage1C"));

		TArray<AActor*>  LevelSequenceActorArray;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), LevelSequenceActorArray);

		for (AActor* Actor : LevelSequenceActorArray)
		{

			ALevelSequenceActor* MidShotActorTemp = Cast<ALevelSequenceActor>(Actor);

			if (MidShotActorTemp && MidShotActorTemp->ActorHasTag(FName("ExitShot")))
			{
				MidShotActor = MidShotActorTemp;
			}
		}

		if (MidShotActor)
		{
			MidShotActor->SequencePlayer->Play();
			MidShotActor->SequencePlayer->OnFinished.AddDynamic(this, &ATriggerActor::OnStage1C);
		}

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveDistanceMarker::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors)
		{
			AObjectiveDistanceMarker* YourClassActor = Cast<AObjectiveDistanceMarker>(Actor);
			if (YourClassActor)
			{
				if (YourClassActor->ActorHasTag(FName("Stage1")))
				{
					YourClassActor->SetActorHiddenInGame(true);
				}
			}

		}
	}



	
}

void ATriggerActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


}

void ATriggerActor::OnStage1C()
{
	
	if (SlashChar && ArrowComponent && EntryOverlap)
	{
		//EntryOverlap->SetGenerateOverlapEvents(false);
		SlashChar->SlashGameStage = EGameStage::EGS_Stage1C;


		//UE_LOG(LogTemp, Warning, TEXT("Slash Triggered"));
		SlashChar->SetActorLocation(ArrowComponent->GetComponentLocation());
		SlashChar->SetActorRotation(ArrowComponent->GetComponentRotation());
		SlashChar->GetController()->SetControlRotation(ArrowComponent->GetComponentRotation());
		SlashChar->PublicDodge();
		SlashChar->SetEquippedWeaponHidden(false);


		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveDistanceMarker::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors)
		{
			AObjectiveDistanceMarker* YourClassActor = Cast<AObjectiveDistanceMarker>(Actor);
			if (YourClassActor)
			{
				if (YourClassActor->ActorHasTag(FName("Stage2")))
				{
					YourClassActor->SetActorHiddenInGame(false);
				}
			}
		}
	}
}

void ATriggerActor::OnStage2C()
{
	
	UGameplayStatics::OpenLevel(GetWorld(), FName("Stylized_Egypt_Demo"));


}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

