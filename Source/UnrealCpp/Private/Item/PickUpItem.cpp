// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUpItem.h"
#include "Player/InventoryOwner.h"

void APickUpItem::OnPickUpComolete_Implementation()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem, ItemCount);
		UE_LOG(LogTemp, Log, TEXT("APickupWeapon::OnPickupComplete_Implementation2"));

	}

	Super::OnPickUpComolete_Implementation();
}
