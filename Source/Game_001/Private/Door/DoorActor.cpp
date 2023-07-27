// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorActor.h"
#include "InventoryComponent.h"
#include "Character/SlashCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UBoxComponent>(FName("Base"));
	RootComponent = Base;


	DoorOverlap = CreateDefaultSubobject<UBoxComponent>(FName("DoorOverlap"));
	DoorOverlap->SetupAttachment(Base);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DoorMesh"));
	DoorMesh->SetupAttachment(Base);
	

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(FName("InventoryComponent"));



}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	DoorOverlap->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnBoxOverlap);

	DoorOverlap->OnComponentEndOverlap.AddDynamic(this, &ADoorActor::OnBoxEndOverlap);
}

void ADoorActor::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Key"));
	if (OtherActor)
	{
		ASlashCharacter* SlashChar = Cast<ASlashCharacter>(OtherActor);

		if (SlashChar)
		{
			
			SlashChar->SetDoorActor(this);
			SlashChar->CreateDoorInventoryWidget();
		}

		

	}
}

void ADoorActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ASlashCharacter* SlashChar = Cast<ASlashCharacter>(OtherActor);

		if (SlashChar)
		{
			SlashChar->SetDoorActor(nullptr);
			SlashChar->DestroyDoorInventoryWidget();
		}



	}
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SubmittedKeys == 1)
	{
		LiftUp();
	}

}

void ADoorActor::LiftUp()
{
}

