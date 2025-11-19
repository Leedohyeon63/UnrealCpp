// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WeaponManager.h"
#include "Weapon/WeaponActor.h"
#include "Weapon/UsedWeapon.h"
#include "Item/PickUp.h"

// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerPlayer = Cast<AActionCharacter>(GetOwner());

	ValidateWeaponDataBase();
	SpawnWeaponInstances();

	OwnerPlayer->EquipWeapon(EItemCode::BasicWeapon);
}

TSubclassOf<APickUp> UWeaponManager::GetPickupWeaponClass(EItemCode InType) const
{
	const UWeaponDataAsset* dataAsset = *WeaponDatabase.Find(InType);
	return dataAsset->PickupWeaponClass;
}


void UWeaponManager::ValidateWeaponDataBase()
{
	if (WeaponDatabase.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("무기 데이터베이스가 비었음!!!"));
	}
	else
	{
		for (const auto& pair : WeaponDatabase)
		{
			if (!pair.Value)
			{
				UE_LOG(LogTemp, Error, TEXT("무기(%d)의 데이터가 null"), static_cast<int32>(pair.Key));
			}
			else if (!pair.Value->IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("무기(%d)의 데이터가 유효하지 않습니다."), static_cast<int32>(pair.Key));
			}
			else if (pair.Key != pair.Value->WeaponType)
			{
				UE_LOG(LogTemp, Warning, TEXT("무기(%d)의 키값과 데이터 타입이 서로 다릅니다."), static_cast<int32>(pair.Key));
			}
		}
	}
}

AWeaponActor* UWeaponManager::GetEquippedWeapon(EItemCode InType) const
{
	//if (const TObjectPtr<AWeaponActor>* weapon = WeaponInstances.Find(InType))
	//{
	//	return *weapon;
	//}

	AWeaponActor* weapon = nullptr;
	if (WeaponInstances.Contains(InType))
	{
		weapon = WeaponInstances[InType];
	}

	return weapon;
}

TSubclassOf<AUsedWeapon> UWeaponManager::GetUsedWeaponClass(EItemCode InType) const
{
	const UWeaponDataAsset* dataAsset = *WeaponDatabase.Find(InType);
	return dataAsset->UsedWaeponClass;
}


void UWeaponManager::SpawnWeaponInstances()
{
	// 불필요한 중괄호 제거
	WeaponInstances.Empty(WeaponDatabase.Num());

	if (OwnerPlayer.IsValid())
	{
		UWorld* world = GetWorld();
		FVector defaultLocation = FVector(0.0f, 0.0f, -10000.0f);
		for (const auto& pair : WeaponDatabase)
		{
			AWeaponActor* weapon = world->SpawnActor<AWeaponActor>(
				pair.Value->EquippedWeaponClass,
				defaultLocation,
				FRotator::ZeroRotator);

			if (weapon) // 안전장치: 생성 확인
			{
				weapon->AttachToComponent(
					OwnerPlayer->GetMesh(),
					FAttachmentTransformRules::KeepWorldTransform,
					FName("root"));
				weapon->SetWeaponOwner(OwnerPlayer.Get());
				weapon->WeaponActivate(false);

				WeaponInstances.Add(pair.Key, weapon);
			}
		}
	}
}



