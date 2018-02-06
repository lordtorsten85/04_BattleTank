// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward declaraction
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Initialize barrel and turret when a valid tank is found
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Gets recommended trajectory to hit target
	void AimAt(FVector HitLocation);

	// Fire, obviously
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:
	// Set state based on reload speed
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;

	//Move barrel towards crosshairs
	void MoveBarrelTowards(FVector AimDirection);

	//Determines if the barrel is moving or not
	bool IsBarrelMoving();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 8000; // Starting value of 8m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3; //Reload time

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //Projectile used on this tank

	double LastFireTime = 0; // Used for reloading

	FVector AimDirection;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	int32 AmmoCount = 3;

};
