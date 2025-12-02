// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Useabel/GoldDataAsset.h"
#include "Player/InventoryOwner.h"
void UGoldDataAsset::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UInventoryOwner>())
	{
		int32 Gold = FMath::RandRange(GoldMin, GoldMax);
		IInventoryOwner::Execute_AddMoney(InTarget, Gold);
	}

}
