// Fill out your copyright notice in the Description page of Project Settings.


#include "DTank.h"

#include "DCannon.h"
#include "DTankInputConfigData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"

// Sets default values
ADTank::ADTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	LeftWheelStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("LeftWheelMesh");
	RightWheelStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("RightWheelMesh");
	CannonChildActorComp = CreateDefaultSubobject<UChildActorComponent>("CannonChildActor");

	// In case I decide to move away from physics based movement
	// MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");

	RootComponent = BodyStaticMeshComp;
	LeftWheelStaticMeshComp->SetupAttachment(RootComponent);
	RightWheelStaticMeshComp->SetupAttachment(RootComponent);
	CannonChildActorComp->SetupAttachment(RootComponent);

	BodyStaticMeshComp->SetSimulatePhysics(true);
	BodyStaticMeshComp->SetMassOverrideInKg(EName::None, 400.0f);
	// Note: If roll ever does become a problem, I will just lock the X-axis rotation
	//BodyStaticMeshComp->BodyInstance.bLockXRotation = true;
	BodyStaticMeshComp->SetAngularDamping(50.0f);
}

// Called when the game starts or when spawned
void ADTank::BeginPlay()
{
	Super::BeginPlay();

	// Just sorting a ref to the player controller as I don't want to have to regrab it everytime I need it
	PlayerControllerRef = GetController<APlayerController>();
	check(PlayerControllerRef);

	// Casts the CannonChildActorComp's actor to a DCannon and stores a ref to it
	if (AActor* CannonChildActor = CannonChildActorComp->GetChildActor())
	{
		CannonRef = Cast<ADCannon>(CannonChildActor);
		if (!CannonRef)
		{
			UE_LOG(LogTemp, Error, TEXT("The Child Actor of CannonChildActorComp does not derive from DCannon on %s"), *GetName())
		}
	}
	else UE_LOG(LogTemp, Error, TEXT("No Child Actor Class assigned to CannonChildActorComp on %s"), *GetName())
}

void ADTank::Move(const FInputActionValue& Value)
{
	// In case I decide to move away from physics based movement
	//AddMovementInput(GetActorForwardVector(), Value.Get<float>(), true);
	
	BodyStaticMeshComp->AddForce(GetActorForwardVector() * Value.Get<float>() * MovementForce);

	// Note: Note seeing any need to clamp the velocity right now as the maps will be extremely small
}

void ADTank::Rotate(const FInputActionValue& Value)
{
	const FRotator CurrentRotation = GetActorRotation();
	const FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw + (RotationSpeed * Value.Get<float>()), CurrentRotation.Roll);
	SetActorRotation(NewRotation);
}

// Called every frame
void ADTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotates the cannon to face the player's mouse location
	if (PlayerControllerRef)
	{
		float MouseScreenPosX;
		float MouseScreenPosY;
		PlayerControllerRef->GetMousePosition(MouseScreenPosX, MouseScreenPosY);

		FVector MousePosToWorldPos;
		FVector MouseDirection;
		PlayerControllerRef->DeprojectScreenPositionToWorld(MouseScreenPosX, MouseScreenPosY, MousePosToWorldPos, MouseDirection);

		FVector TargetLocation = FMath::LinePlaneIntersection(MousePosToWorldPos, MousePosToWorldPos + (MouseDirection * 1000), GetActorLocation(), FVector(0, 0, 1));
	
		CannonRef->UpdateAimLRotation(TargetLocation);	
	}
}

// Called to bind functionality to input
void ADTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());
	check(PC);

	// Gets the local player's enhanced input subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	
	// If there are any mappings, they are cleared 
	Subsystem->ClearAllMappings();
	// Adds the DTankInputConfigData as a mapping to the local player's enhanced input subsystem
	check(InputMapping)
	Subsystem->AddMappingContext(InputMapping, 0);

	// Binds the move and rotate actions to a function that is called when the action is triggered
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InputConfigData->InputMove, ETriggerEvent::Triggered, this, &ADTank::Move);
	EnhancedInputComponent->BindAction(InputConfigData->InputRotate, ETriggerEvent::Triggered, this, &ADTank::Rotate);
}

