// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/PickUpConsume.h"
#include "Player/InventoryOwner.h"

void APickUpConsume::OnPickUpComolete_Implementation()
{
	OnConsume();
	Super::OnPickUpComolete_Implementation();
}

void APickUpConsume::OnConsume()
{
	if (DataAsset)
	{
		DataAsset->Excute(PickupOwner.Get());
	}
}