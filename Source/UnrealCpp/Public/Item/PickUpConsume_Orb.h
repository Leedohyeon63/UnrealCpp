// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickUpConsume.h"
#include "PickUpConsume_Orb.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickUpConsume_Orb : public APickUpConsume
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealOrb")
	float HealAmount = 30.0f;
protected:
	virtual void OnConsume()override;
	
};
