// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DTank.generated.h"

class UInputMappingContext;
class UDTankInputConfigData;
class ADCannon;
struct FInputActionValue;

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

	// In case I decide to move away from physics based movement
	/*UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* MovementComp;*/

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UDTankInputConfigData* InputConfigData;

	// The amount of force to apply to the tank in it's forward direction while moving
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MovementForce = 500000.0f;

	// The speed at which to rotate the tank while rotating
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RotationSpeed = .5f;

	UPROPERTY(EditDefaultsOnly)
	UChildActorComponent* CannonChildActorComp;

	UPROPERTY(BlueprintReadOnly)
	ADCannon* CannonRef;

	UPROPERTY()
	APlayerController* PlayerControllerRef; 
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveInput(const FInputActionValue& Value);
	
	void RotateInput(const FInputActionValue& Value);
	
	void PrimaryFireInput(const FInputActionValue& Value);

	/** Moves the tank either forwards or backwards
	 * @param Direction If > 0, the tank will move forward. If < 0, the tank will move backwards
	 **/
	UFUNCTION(BlueprintCallable)
	virtual void Move(float Direction);

	/** Moves the tank either forwards or backwards
	 * @param Direction If > 0, the tank will rotate right. If < 0, the tank will rotate left
	 **/
	UFUNCTION(BlueprintCallable)
	virtual void Rotate(float Direction);

	// Notifies the tanks cannon to fire a projectile
	UFUNCTION(BlueprintCallable)
	virtual void PrimaryFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
