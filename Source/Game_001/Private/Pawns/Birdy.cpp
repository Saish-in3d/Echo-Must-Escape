// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Birdy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//#include "Components/CameraComponent.h"

// Sets default values
ABirdy::ABirdy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());
	

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Capsule);
	SpringArm->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABirdy::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ABirdy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABirdy::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
	UE_LOG(LogTemp, Warning, TEXT("gg %f"), Value);
}

void ABirdy::Turn(float Value)
{
	if (Controller && (Value != 0))
	{
		AddControllerYawInput(Value);
	}
	

}

void ABirdy::LookUp(float Value)
{
	if (Controller && (Value != 0))
	{
		float NewValue = Value ;
		AddControllerPitchInput(NewValue);
	}
	
}


// Called to bind functionality to input
void ABirdy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABirdy::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABirdy::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABirdy::LookUp);
}



