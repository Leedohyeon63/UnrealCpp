// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/InventoryOwner.h"
#include "Item/PickUpConsume.h"

void APickUpConsume::OnPickUpComolete_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("APickupWeapon::OnPickupComplete_Implementation"));
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddConsume(PickupOwner.Get(), PickupConsumeItem);
		UE_LOG(LogTemp, Log, TEXT("APickupWeapon::OnPickupComplete_Implementation2"));

	}
	Super::OnPickUpComolete_Implementation();
}
