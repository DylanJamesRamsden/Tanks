// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCannon.generated.h"

class UArrowComponent;
class ADProjectile;

UCLASS()
class TANKS_API ADCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADCannon();

protected:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseStaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BarrelStaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* ProjectileSpawnOriginComp;

	// The speed at which the cannon rotates towards it's target location
	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 15.0f;

	// The projectile class to spawn when Fire() is fired
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADProjectile> ProjectileClass;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Rotates the cannon to face the target location
	void UpdateAimLRotation(const FVector TargetLocation);

	// Fires a projectile from the transform of the ProjectileSpawnOriginComp
	virtual void Fire();
};
