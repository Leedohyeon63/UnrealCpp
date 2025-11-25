// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/PickupFactorySubsystem.h"
#include "Settings/PickupFactorySettings.h"
void UPickupFactorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UPickupFactorySettings* PickupSettings = GetDefault<UPickupFactorySettings>();

	// Settings가 유효하고, Map이 비어있지 않은지 확인
	if (PickupSettings && !PickupSettings->PickupFactories.IsEmpty())
	{
		// TMap 순회 (Key: EItemCode, Value: TSoftClassPtr<APickUp>)
		for (const auto& Pair : PickupSettings->PickupFactories)
		{
			const EItemCode& Code = Pair.Key;
			const TSoftClassPtr<APickUp>& PickUp = Pair.Value;

			if (!PickUp.IsNull())
			{
				UClass* LoadedClass = PickUp.LoadSynchronous();
				if (LoadedClass)
				{
					PickupClass.Add(Code, LoadedClass);
					UE_LOG(LogTemp, Log, TEXT("Loaded Pickup Class for Code %d: %s"), (int32)Code, *LoadedClass->GetName());
				}
			}
		}
	}
}

void UPickupFactorySubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("Deinitialize"));
	Super::Deinitialize();
}

APickUp* UPickupFactorySubsystem::SpawnPickup(EItemCode ItemCode, FVector Location, FRotator Rotation)
{
	// 1. 요청된 코드가 맵에 있는지 확인
	if (const TSubclassOf<APickUp>* SpawnPickUpClass = PickupClass.Find(ItemCode))
	{
		// 2. 클래스가 유효한지 확인 (*FoundClass로 실제 값 접근)
		if (*SpawnPickUpClass)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				// 3. 실제 스폰 수행
				APickUp* NewPickup = World->SpawnActor<APickUp>(*SpawnPickUpClass, Location, Rotation, SpawnParams);

				if (NewPickup)
				{
					return NewPickup;
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Failed to spawn pickup for code: %d"), (int32)ItemCode);
	return nullptr;
}
