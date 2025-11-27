// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickUpConsume.h"
#include "PickUpConsumeMoney.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickUpConsumeMoney : public APickUpConsume
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 Money = 100;
protected:
	virtual void OnConsume()override;
};
