// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Item/PickUp.h"
#include "Common/CommonEnum.h"
#include "PickupFactorySettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Pickup Factory Settings"))
class UNREALCPP_API UPickupFactorySettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	TMap<EItemCode, TSoftClassPtr<APickUp>> PickupFactories;
};
