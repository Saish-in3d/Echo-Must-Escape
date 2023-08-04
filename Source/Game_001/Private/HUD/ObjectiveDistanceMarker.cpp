// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjLocationWidgetComponent.h"
#include "Components/BoxComponent.h"
#include "HUD/ObjectiveDistanceMarker.h"
#include "Math/UnrealMathUtility.h" 
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectiveDistanceMarker::AObjectiveDistanceMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UBoxComponent>(FName("BaseComponent"));
	if(Base)
	{
		SetRootComponent(Base);
	}

	ObjLocWidgetComp = CreateDefaultSubobject<UObjLocationWidgetComponent>(FName("ObjLocationWidgetComponent"));
	
	if (ObjLocWidgetComp)
	{
		ObjLocWidgetComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		ObjLocWidgetComp->SetVisibility(true);

	}

}

// Called when the game starts or when spawned
void AObjectiveDistanceMarker::BeginPlay()
{
	Super::BeginPlay();

	
	
}

FText AObjectiveDistanceMarker::CalculateObjDistance()
{
	FVector MarkerLocation = GetActorLocation();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr) { return FText(); }

	FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

	double MarkerDistanceAbs = (MarkerLocation - PlayerLocation).Size();

	double RoundedMarkerDist = (FMath::RoundToInt(MarkerDistanceAbs))/100;

	FText DisplayText = FText::AsNumber(RoundedMarkerDist);

	FText Part2 = FText::FromString(TEXT(" m"));

	FText FormatString = FText::FromString(TEXT("{0}{1}"));

	FText FinalValue = FText::Format(FormatString, DisplayText, Part2);



	return FinalValue;
}

// Called every frame
void AObjectiveDistanceMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ObjLocWidgetComp)
	{
		
		ObjLocWidgetComp->SetDistanceText();
	}

}

