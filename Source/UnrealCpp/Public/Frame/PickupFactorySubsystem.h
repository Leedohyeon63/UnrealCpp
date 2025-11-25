// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Common/CommonEnum.h"
#include "Item/PickUp.h"
#include "PickupFactorySubsystem.generated.h"
/**
 * 
 */
UCLASS()
class UNREALCPP_API UPickupFactorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Pickup Factory")
	APickUp* SpawnPickup(EItemCode ItemCode, FVector Location, FRotator Rotation = FRotator::ZeroRotator);
protected:
	UPROPERTY()
	TMap<EItemCode, TSubclassOf<APickUp>> PickupClass;

};
