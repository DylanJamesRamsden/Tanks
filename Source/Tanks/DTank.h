// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DTank.generated.h"

UCLASS()
class TANKS_API ADTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADTank();

protected:

	// The static mesh that represents the tank's body
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BodyStaticMeshComp;

	// @TODO In the future, if the tank has moving wheels and what not these would need to be a USkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftWheelStaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightWheelStaticMeshComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
