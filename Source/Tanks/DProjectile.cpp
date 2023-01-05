// Fill out your copyright notice in the Description page of Project Settings.


#include "DProjectile.h"

#include "DTank.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADProjectile::ADProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ParticleTrailComp = CreateDefaultSubobject<UNiagaraComponent>("ParticleTrail");

	RootComponent = StaticMeshComp;
	ParticleTrailComp->SetupAttachment(RootComponent);

	ProjectileMovementComp->InitialSpeed = 2000.0f;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
	ProjectileMovementComp->bShouldBounce = true;
	// Only .7f of the projectiles velocity is carried over once a bounce is made
	ProjectileMovementComp->Bounciness = 0.7f;
}

// Called when the game starts or when spawned
void ADProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);
	
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ADProjectile::OnProjectileHit);
}

// Called every frame
void ADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->IsA(ADTank::StaticClass()))
	{
		// If we still have bounces to make we just increment the number of bounces made by 1, otherwise the projectile
		// is just destroyed
		if (BouncesMade != BouncesAllowed)
		{
			BouncesMade++;
		}
		else Destroy();
	}
	else
	{
		// Apply damage to other tank
		
		Destroy();
	}
}

