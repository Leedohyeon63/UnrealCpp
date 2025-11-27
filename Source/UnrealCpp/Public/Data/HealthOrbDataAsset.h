// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConsumableDataAsset.h"
#include "HealthOrbDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UHealthOrbDataAsset : public UConsumableDataAsset
{
	GENERATED_BODY()
public:
	virtual void OnConsume()override;
};
