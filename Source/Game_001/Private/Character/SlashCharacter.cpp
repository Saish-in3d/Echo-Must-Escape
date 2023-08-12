// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Item/MyActor.h"
#include "Animation/AnimMontage.h"
#include "Item/Weapons/Weapon.h"
#include "Components/AttributeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HUD/PauseMenuWidget.h"
#include "HUD/ObjectiveDistanceMarker.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "HUD/SlashHUD.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/Enemy.h"
#include "SlashOverlayWidget.h"
// Sets default values
ASlashCharacter::ASlashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels( ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

}





float ASlashCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;
}

void ASlashCharacter::Jump()
{
	if (IsUnoccupied())
	{
		Super::Jump();
	}
}

bool ASlashCharacter::HasEnoughStamina()
{
	return  Attributes && Attributes->GetStamina() > Attributes->GetDodgeCost();
}

bool ASlashCharacter::IsOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}

// Called when the game starts or when spawned
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("EngageableTarget"));
	Tags.Add(FName("Slash"));


	
}

void ASlashCharacter::MoveForward(float Value)
{
	if (Controller && (Value != 0.f)&& ActionState == EActionState::EAS_Unoccupied )
	{
		//FVector Forward = GetActorForwardVector();
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}
}

void ASlashCharacter::LookUp(float Value)
{
	
	
	AddControllerPitchInput(Value);
	
}

void ASlashCharacter::Turn(float Value)
{
	
	
	AddControllerYawInput(Value);
	
}

void ASlashCharacter::MoveRight(float Value)
{
	if (Controller && (Value != 0) && ActionState == EActionState::EAS_Unoccupied)
	{
		//FVector Right = GetActorRightVector();
		const FRotator ControlRotation = GetControlRotation();
		const FRotator ControlRotationYaw(0.f, ControlRotation.Yaw, 0.f);
		const FVector Right = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Right, Value);
	}
	
}

void ASlashCharacter::Equip_E()
{
	
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingActorr);
	//&& CharacterState == ECharacterState::ECS_Unequipped  && ItemState == EItemState::EIS_Hovering
	if (OverlappingActorr)
	{
		
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"), this);
		OverlappingWeapon->SetOwner(this);
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString("E PRESSED"));
		OverlappingActorr = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}
	else 
	{
		
		if (CanDisarm())
		{
			ActionState = EActionState::EAS_Attacking;
			FName SectionName = FName("Unequip");
			PlayEquipMontage(SectionName);
			//OverlappingActorr = nullptr;
			CharacterState = ECharacterState::ECS_Unequipped;
			//ActionState = EActionState::EAS_Unoccupied;
		
		}
		else if (CanArm())
		{
			ActionState = EActionState::EAS_Attacking;
			FName SectionName = FName("Equip");
			PlayEquipMontage(SectionName);
			CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
			//ActionState = EActionState::EAS_Unoccupied;
			
		}
	}

	
}

void ASlashCharacter::Attack()
{
	if(ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_EquippedOneHandedWeapon && ActionState != EActionState::EAS_HitReaction)
	{
		ActionState = EActionState::EAS_Attacking;
		UE_LOG(LogTemp, Warning, TEXT("Echo"));
		PlayAttackMontage();
		//AttackEnd();
	}
}

void ASlashCharacter::Dodge()
{
	if (IsOccupied() || !HasEnoughStamina()) return;
	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;

	if (Attributes && SlashOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void ASlashCharacter::AttackEnd()
{
	if (EquippedWeapon)
	{
		ActionState = EActionState::EAS_Unoccupied;
	}
}

void ASlashCharacter::Disarm()
{
	if (EquippedWeapon)
	{
		ActionState = EActionState::EAS_Attacking;
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
		CharacterState = ECharacterState::ECS_Unequipped;
	}
}

void ASlashCharacter::Arm()
{
	if (EquippedWeapon)
	{
		ActionState = EActionState::EAS_Attacking;
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

void ASlashCharacter::ReactEnd()
{

	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::Die()
{
	Super::Die();

	ActionState = EActionState::EAS_Dead;
	DisableMeshCollision();



	if (SlashOverlay)
	{
		SlashOverlay->RemoveFromViewport();
	}


	TArray<AActor*> FoundActorsM;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveDistanceMarker::StaticClass(), FoundActorsM);

	for (AActor* ActorM : FoundActorsM)
	{
		AObjectiveDistanceMarker* YourClassActorM = Cast<AObjectiveDistanceMarker>(ActorM);
		if (YourClassActorM)
		{
			//UE_LOG(LogTemp, Warning, TEXT("HiddenActor"));
			YourClassActorM->SetActorHiddenInGame(true);
		}
	}

	GetWorldTimerManager().SetTimer(AfterDeathTimer, this, &ASlashCharacter::AfterDeathSequence, AfterDeathDelay, false);
}

void ASlashCharacter::DodgeEnd()
{
	Super::DodgeEnd();

	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString("E RE PRESSED"));
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
	//ActionState = EActionState::EAS_Unoccupied;

}




// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASlashCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASlashCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ASlashCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASlashCharacter::MoveRight);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ASlashCharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip_E"), IE_Pressed, this, &ASlashCharacter::Equip_E);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &ASlashCharacter::Attack);
	PlayerInputComponent->BindAction(FName("Dodge"), IE_Pressed, this, &ASlashCharacter::Dodge);
	PlayerInputComponent->BindAction(FName("Pause"), IE_Pressed, this, &ASlashCharacter::PauseGame);
	PlayerInputComponent->BindAction(FName("Tab"), IE_Pressed, this, &ASlashCharacter::OpenInventory);

	
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SlashOverlay == nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());
			if (SlashHUD)
			{
				SlashOverlay = SlashHUD->GetSlashOverlay();
				if (SlashOverlay && Attributes)
				{
					//SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
					SlashOverlay->SetStaminaBarPercent(1.f);


				}
			}
		}
	}



	if (Attributes && SlashOverlay)
	{

		Attributes->RegenStamina(DeltaTime);
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());


	}


}




void ASlashCharacter::GetHit_Implementation(const FVector& ImpactPoint)
{
	ActionState = EActionState::EAS_HitReaction; 
	WeaponColliisionEnabled(ECollisionEnabled::NoCollision);
	if (IsCharacterAlive())
		//IsCharacterAlive()
	{
		DirectionalHit(ImpactPoint);
	}
	else Die();
	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		ActionState = EActionState::EAS_HitReaction;
	}
}

void ASlashCharacter::SetOverlappingItem(AMyActor* Item)
{
	OverlappingActorr = Item;
}

bool ASlashCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped && EquippedWeapon && EquipMontage;
}

bool ASlashCharacter::CanArm()
{
	return  ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_Unequipped && EquippedWeapon && EquipMontage;
}

void ASlashCharacter::InitializeSlashOverlay()
{
	
}

void ASlashCharacter::UpdateSlashOverlayHealth()
{

	if (SlashOverlay && Attributes)
	{
		SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());


	}
}

void ASlashCharacter::CreateDoorInventoryWidget()
{

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && DoorInventoryWidgetClass)
	{


		DoorOverlay = CreateWidget<UUserWidget>(PlayerController, DoorInventoryWidgetClass);


	}
	if (DoorOverlay)
	{
		//UE_LOG(LogTemp, Warning, TEXT("My int32 value"));
		DoorOverlay->AddToViewport();
	}
	

}

void ASlashCharacter::DestroyDoorInventoryWidget()
{
	if (DoorOverlay)
	{
		//UE_LOG(LogTemp, Warning, TEXT("My int32 value"));
		DoorOverlay->RemoveFromViewport();
	}
}

void ASlashCharacter::PublicDodge()
{
	Dodge();
}

bool ASlashCharacter::IsUnoccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}

void ASlashCharacter::SetHUDHealth()
{
	if (SlashOverlay && Attributes)
	{

		SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

void ASlashCharacter::PauseGame()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(nullptr);
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;

		if (PauseWidgetClass)
		{
			 PauseMenuWidget = CreateWidget<UPauseMenuWidget>(PlayerController, PauseWidgetClass);


			if (PauseMenuWidget)
			{
				PauseMenuWidget->AddToViewport();
			}

		}
			
			
		
	}



}

void ASlashCharacter::AfterDeathSequence()
{
	TArray<AActor*> FoundActorsD;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActorsD);

	for (AActor* ActorD : FoundActorsD)
	{


		AEnemy* EnemyTemp = Cast<AEnemy>(ActorD);
		if (EnemyTemp)
		{
			EnemyTemp->Die();

		}

	}

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
		EndScreenWidget = CreateWidget<UUserWidget>(GetWorld(), EndScreenWidgetClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport();
			APlayerController* Controllertemp = GetWorld()->GetFirstPlayerController();
			if (Controllertemp)
			{
				FInputModeUIOnly InputMode;
				Controllertemp->SetInputMode(InputMode);
				Controllertemp->bShowMouseCursor = true;
			}
		}
		FinalShotActor->SequencePlayer->OnFinished.AddDynamic(this, &ASlashCharacter::OnStageFC);


	}



}

void ASlashCharacter::OnStageFC()
{

	UGameplayStatics::OpenLevel(GetWorld(), FName("Stylized_Egypt_Demo"));

}

void ASlashCharacter::OpenInventory()
{
	InventoryWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);

	if (InventoryWidget)
	{
		InventoryWidget->AddToViewport();
		APlayerController* Controllertemp = GetWorld()->GetFirstPlayerController();
		if (Controllertemp)
		{
			FInputModeGameAndUI  InputMode;
			Controllertemp->SetInputMode(InputMode);
			Controllertemp->bShowMouseCursor = true;
		}
	}

}





