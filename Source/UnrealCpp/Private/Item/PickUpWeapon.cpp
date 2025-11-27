// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUpWeapon.h"
#include "Player/InventoryOwner.h"

void APickUpWeapon::OnPickUpComolete_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("APickupWeapon::OnPickupComplete_Implementation"));
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddWeapon(PickupOwner.Get(), PickupItem, UseCount);
		UE_LOG(LogTemp, Log, TEXT("APickupWeapon::OnPickupComplete_Implementation2"));

	}

	Super::OnPickUpComolete_Implementation();
}
