// Fill out your copyright notice in the Description page of Project Settings.


#include "DCannon.h"

#include "DProjectile.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADCannon::ADCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BarrelStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	ProjectileSpawnOriginComp = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnOrigin");

	RootComponent = BaseStaticMeshComp;
	BarrelStaticMeshComp->SetupAttachment(RootComponent);
	ProjectileSpawnOriginComp->SetupAttachment(BarrelStaticMeshComp);
}

// Called when the game starts or when spawned
void ADCannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADCannon::UpdateAimLRotation(const FVector TargetLocation)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

	// Interps from the current rotation of the cannon to the target rotation
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(GetActorRotation().Pitch, TargetRotation.Yaw, GetActorRotation().Roll), DeltaTime, RotationSpeed));
}

void ADCannon::Fire()
{
	if (ProjectileClass)
	{
		FActorSpawnParameters ActorSpawnParams;
		AActor* SpawnedProjectile = GetWorld()->SpawnActor<ADProjectile>(ProjectileClass,
			ProjectileSpawnOriginComp->GetComponentLocation(), ProjectileSpawnOriginComp->GetComponentRotation(), ActorSpawnParams);

		if (!SpawnedProjectile)
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not spawn projectile on %s"), *GetName())
		}	
	}
	else UE_LOG(LogTemp, Error, TEXT("No projectile class assigned on %s"), *GetName())
}
