// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Common/CommonEnum.h"
#include "Data/WeaponDataAsset.h"
#include "WeaponManager.generated.h"

class AWeaponActor;
class AUsedWeapon;
class APickUp;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPP_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManager();

	AWeaponActor* GetEquippedWeapon(EWeaponCode InType) const;
	TSubclassOf<AUsedWeapon> GetUsedWeaponClass(EWeaponCode InType) const;
	TSubclassOf<APickUp> GetPickupWeaponClass(EWeaponCode InType) const;

	inline EItemCode GetItemCode(EWeaponCode Code) const
	{
		return WeaponCodeToItemCode[Code];
	};
	inline EWeaponCode GetWeaponCode(EItemCode Code) const
	{
		return ItemCodeToWeaponCode[Code];
	};
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Database")
	TMap<EWeaponCode, TObjectPtr<UWeaponDataAsset>> WeaponDatabase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Instance")
	TMap<EWeaponCode, TObjectPtr<AWeaponActor>> WeaponInstances;

private:
	void ValidateWeaponDataBase();

	void SpawnWeaponInstances();

private:
	UPROPERTY()
	TWeakObjectPtr<class AActionCharacter> OwnerPlayer = nullptr;


	TMap<EItemCode, EWeaponCode> ItemCodeToWeaponCode;
	TMap<EWeaponCode, EItemCode> WeaponCodeToItemCode;
};
