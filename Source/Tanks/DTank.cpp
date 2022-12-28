// Fill out your copyright notice in the Description page of Project Settings.


#include "DTank.h"

#include "DTankInputConfigData.h"
#include "TanksGameModeBase.h"
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

	RootComponent = BodyStaticMeshComp;
	LeftWheelStaticMeshComp->SetupAttachment(RootComponent);
	RightWheelStaticMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADTank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADTank::Move(const FInputActionValue& Value)
{
}

void ADTank::Rotate(const FInputActionValue& Value)
{
}

// Called every frame
void ADTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

