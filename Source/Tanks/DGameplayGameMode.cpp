// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayGameMode.h"

#include "Kismet/GameplayStatics.h"

void ADGameplayGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	// Although this isn't a multiplayer game just yet, I think this is the best place to call this type of logic
	UWorld* World = GetWorld();
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0))
	{
		if (AActor* LevelViewpointActor = UGameplayStatics::GetActorOfClass(World, LevelViewpointClass))
		{
			PC->SetViewTarget(LevelViewpointActor);	
		}
		else
		{
			// @TODO Update this message to also indicate that an actor of this class could be missing from the level
			UE_LOG(LogTemp, Error,
				TEXT("Cannot change level view target because LevelViewpointClass is a nullptr. Please update DGameplayGameMode with a valid subclass!"))
		}
	}
}
