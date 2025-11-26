// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/PickupFactorySubsystem.h"
#include "Settings/PickupFactorySettings.h"
#include "Data/DropItemData_TableRow.h"

void UPickupFactorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("UPickupFactorySubsystem : 초기화 시작"))
	LoadPickupClassesMap();
}

void UPickupFactorySubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("Deinitialize"));
	Super::Deinitialize();
}

APickUp* UPickupFactorySubsystem::SpawnPickup(EItemCode ItemCode, FVector Location, FRotator Rotation)
{
	APickUp* SpawnedPickup = nullptr;
	if (PickupClasses.Contains(ItemCode))
	{
		UWorld* world = GetWorld();
		SpawnedPickup = world->SpawnActor<APickUp>(PickupClasses[ItemCode], Location, Rotation);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPickupFactorySubsystem : 설정되지 않은 Pickup을 생성하려고 합니다."));
	}
	return SpawnedPickup;
}

void UPickupFactorySubsystem::LoadPickupClassesMap()
{
	const UPickupFactorySettings* settings = GetDefault<UPickupFactorySettings>();
	if (settings && !settings->PickupDataTable.IsNull())
	{
		UDataTable* dataTable = settings->PickupDataTable.LoadSynchronous();
		if (dataTable)
		{
			TArray<FPickupItemData_TableRow*> allRows;
			dataTable->GetAllRows(TEXT("PickupDataTable"), allRows);
			for (const FPickupItemData_TableRow* row : allRows)
			{
				if (PickupClasses.Contains(row->PickupCode))
				{
					UE_LOG(LogTemp, Warning, TEXT("UPickupFactorySubsystem : 키 값이 중복입니다. 이전 값은 덮어써집니다."));
				}
				PickupClasses.Add(row->PickupCode, row->PickupClass);
			}
			UE_LOG(LogTemp, Log, TEXT("UPickupFactorySubsystem : DataTable 로딩 완료."))
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UPickupFactorySubsystem : DataTable 로딩 실패!!!"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPickupFactorySubsystem : PickupDataTable is null!!!"))
	}
}
