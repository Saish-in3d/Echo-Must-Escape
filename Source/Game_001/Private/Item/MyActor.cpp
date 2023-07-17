// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "PickupInterface.h"
#include "Components/SphereComponent.h"
// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	
	

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//ItemMesh->SetupAttachment(Sphere);
    SetRootComponent(ItemMesh);

	Sphere->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play Called"));
	GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Blue, FString("oNSCREEN MES SAGE"));
	FVector Location = GetActorLocation();
	//DrawDebugSphere(World, Location, 25.f, 24, FColor::Red, false, 60);  
	//DrawDebugLine(World, Location, Location + GetActorForwardVector() * 100, FColor::Red, true,-1.f, 0.f, 1.f);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnSphereOverlap);

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMyActor::OnSphereEndOverlap);

	
}
void AMyActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(this);
	}

}

void AMyActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}
}

float RunningTime;
// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Nameis: %s"), *Name);
	//UE_LOG(LogTemp, Warning, TEXT("Deltatime: %f"), DeltaTime);

	if(ItemState == EItemState::EIS_Hovering)
	{
		RunningTime += DeltaTime;
		float Disp = FMath::Sin(RunningTime);
		FVector DispVector = FVector(0.f, 0.f, Disp);
		AddActorWorldOffset(DispVector);
	}

}

