// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActor.h"
#include "Item/ConsumableInterface.h"
#include "ConsumableWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponUseEnded);
/**
 * 
 */
UCLASS()
class UNREALCPP_API AConsumableWeapon : public AWeaponActor
{
	GENERATED_BODY()
public:
	virtual void OnAttack() override;
	virtual void OnWeaponPickuped() override;
	virtual bool CanAttack() override { return CurrentUseCount > 0; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	int32 MaxUseCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 CurrentUseCount = 10;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "Weapon")
	FOnConsume OnWeaponUseEnded;
};
