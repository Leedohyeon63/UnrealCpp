// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickUp.h"
#include "Common/CommonEnum.h"
#include "PickUpWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickUpWeapon : public APickUp
{
	GENERATED_BODY()
public:
	virtual void OnPickUpComolete_Implementation() override;

	inline void SetWeaponUseCount(int32 InCount) { UseCount = InCount; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp|Weapon")
	EWeaponCode PickupItem = EWeaponCode::BasicWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Weapon")
	int32 UseCount = 1;
};
