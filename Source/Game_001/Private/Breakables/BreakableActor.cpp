// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakables/BreakableActor.h"
#include "Item/Treasure/Treasure.h"
#include "Components/CapsuleComponent.h"
#include "Inventory/HealthPickup.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = true;



	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	//GeometryCollection->SetupAttachment(GetRootComponent());
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
	BreakableCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BreakableCapsule"));
	//BreakableCapsule->SetupAttachment(GetRootComponent());
	BreakableCapsule->AttachToComponent(GeometryCollection, FAttachmentTransformRules::KeepRelativeTransform);
	
	BreakableCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	//NewCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("NewCapsule"));

	//NewSceneComponent = CreateDefaultSubobject<USceneComponent>(FName("NewSceneComponent"));
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableActor::GetHit_Implementation(const FVector& ImpactPoint)
{
	if (HasHit) { return; }
	HasHit = true;
	UWorld* World = GetWorld();
	if(BreakableCapsule)
	{
		BreakableCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	}
	if (World && TreasureClassess.Num() > 0)
	{
		FVector Location = GetActorLocation();
		Location.Z += 75.f;

		int32 Selection1 = FMath::RandRange(0, 10);
		if (Selection1 == 1 || Selection1 == 2 || Selection1 == 3)
		{

			int32 Selection2 = FMath::RandRange(0, TreasureClassess.Num() - 1);

			if(TreasureClassess[Selection2])
			{
				World->SpawnActor<ATreasure>(TreasureClassess[Selection2], Location, GetActorRotation());
			}
		}
		else
		{
			if(HealthPickupClass)
			{
				World->SpawnActor<AHealthPickup>(HealthPickupClass, Location, GetActorRotation());
			}
		}


	}
}

