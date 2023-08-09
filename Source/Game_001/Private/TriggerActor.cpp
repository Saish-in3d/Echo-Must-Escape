// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SlashCharacter.h"

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
	if (SlashChar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slash Triggered"));
		SlashChar->SetEquippedWeaponHidden(true);
	}


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
		MidShotActor->SequencePlayer->OnFinished.AddDynamic(this, &ATriggerActor::OnSequencePlaybackFinished);
	}
			


}

void ATriggerActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


}

void ATriggerActor::OnSequencePlaybackFinished()
{
	if (SlashChar)
	{
		FVector Loctaton = FVector(-650.000000, -6910.000000, 100.000000);
		FRotator Rotation = FRotator( 0.000000,  -270.000000,  0.000000);
		SlashChar->TeleportTo(Loctaton, Rotation);
		SlashChar->SetEquippedWeaponHidden(false);
	}

}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

