// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Treasure/Treasure.h"
#include "Character/SlashCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* SlashCharacterr = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacterr)
	{
		if (CoinSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				CoinSound,
				GetActorLocation()
			);
		}
		Destroy();
	}
}

