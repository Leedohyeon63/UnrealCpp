// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickUp.h"
#include "Common/CommonEnum.h"
#include "PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickUpItem : public APickUp
{
	GENERATED_BODY()
public:
	virtual void OnPickUpComolete_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp|Item")
	EItemCode PickupItem = EItemCode::Crown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp|Item")
	EItemCode PickupItem = EItemCode::Crown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Item")
	int32 ItemCount = 1;
};
