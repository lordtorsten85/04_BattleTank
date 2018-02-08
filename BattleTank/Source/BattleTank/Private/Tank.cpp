// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0 ,CurrentHealth);


	UE_LOG(LogTemp, Warning, TEXT("Damage Amount: %f"), DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("Damage to Apply: %i"), DamageToApply);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TANK IS DEAD"));
	}

	return DamageToApply;
}
