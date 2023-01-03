// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TANKS_API ADProjectile : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComp;
	
	// Sets default values for this actor's properties
	ADProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
