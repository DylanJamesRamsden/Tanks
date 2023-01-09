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
	UPROPERTY(EditDefaultsOnly, Category = "Ballistics")
	TSubclassOf<ADProjectile> ProjectileClass;

	// How long (in seconds) until the next projectile can be fired. If 0.0f, there is no reload time.
	UPROPERTY(EditDefaultsOnly, Category = "Ballistics")
	float ReloadTime = 0.5f;

	// Whether or not the cannon can fire a projectile
	bool bIsArmed = true;

	FTimerHandle ReloadTimerHandle;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnReloadComplete();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Rotates the cannon to face the target location
	void UpdateAimLRotation(const FVector TargetLocation);

	// Fires a projectile from the transform of the ProjectileSpawnOriginComp
	virtual void Fire();
};
