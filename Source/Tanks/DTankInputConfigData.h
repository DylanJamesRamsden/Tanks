// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DTankInputConfigData.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class TANKS_API UDTankInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputRotate;
};
