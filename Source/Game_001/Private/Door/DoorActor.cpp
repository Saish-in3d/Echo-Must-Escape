// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorActor.h"
#include "InventoryComponent.h"
#include "Character/SlashCharacter.h"
#include "KeyItem.h"
#include "Math/Quat.h"
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

	

	 StartRotation = FRotator(0.0f, 0.10f, 0.0f).Quaternion();

	 EndRotation = FRotator(0.0f, -89.0f, 0.0f).Quaternion();
}

void ADoorActor::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
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

void ADoorActor::AddKeyToDoor()
{
	UKeyItem* KeyItemObject = NewObject< UKeyItem>(UKeyItem::StaticClass());
	if(InventoryComponent && KeyItemObject)
	{
		SubmittedKeys += 1;
		KeyItemObject->IsKeyUsed = true;
		InventoryComponent->AddItem(KeyItemObject);
	}


}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SubmittedKeys == 10)
	{
		OpenDoor();
	}

	

	
	
}

void ADoorActor::OpenDoor()
{
	if (DoorMesh)
	{
		if (Alpha <= 0.95f)
		{

			Alpha += 0.1;

			FQuat Result = FQuat::Slerp(StartRotation, EndRotation, Alpha);


			DoorMesh->SetRelativeRotation(Result);
		}
	}


}

