// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DProjectile.generated.h"

class UProjectileMovementComponent;
class UNiagaraComponent;

UCLASS()
class TANKS_API ADProjectile : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* ParticleTrailComp;

	// How many times the projectile can bounce off of surfaces before it is destroyed
	UPROPERTY(EditDefaultsOnly)
	int32 BouncesAllowed = 1;

	int32 BouncesMade;
	
	// Sets default values for this actor's properties
	ADProjectile();

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
