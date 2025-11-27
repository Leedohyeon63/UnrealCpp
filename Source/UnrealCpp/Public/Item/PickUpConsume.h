// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickUp.h"
#include "PickUpConsume.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickUpConsume : public APickUp
{
	GENERATED_BODY()
public:
	virtual void OnPickUpComolete_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp|Weapon")
	EItemCode PickupConsumeItem = EItemCode::HPOrb;

};
