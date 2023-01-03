// Fill out your copyright notice in the Description page of Project Settings.


#include "DProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADProjectile::ADProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void ADProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

