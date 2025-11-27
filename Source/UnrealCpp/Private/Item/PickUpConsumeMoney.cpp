// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUpConsumeMoney.h"
#include "Player/InventoryOwner.h"

void APickUpConsumeMoney::OnConsume()
{
	Super::OnConsume();

	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddMoney(PickupOwner.Get(), Money);
	}
}
