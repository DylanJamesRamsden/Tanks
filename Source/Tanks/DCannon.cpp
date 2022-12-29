// Fill out your copyright notice in the Description page of Project Settings.


#include "DCannon.h"

// Sets default values
ADCannon::ADCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

