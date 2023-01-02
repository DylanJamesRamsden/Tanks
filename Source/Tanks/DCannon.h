// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCannon.generated.h"

class UArrowComponent;

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

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 15.0f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Rotates the cannon to face the target location
	void UpdateAimLocation(const FVector TargetLocation);
};
