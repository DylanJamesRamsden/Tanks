// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameplayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ADGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	// The class to search for when looking for an actor to view the level from
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> LevelViewpointClass;
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
