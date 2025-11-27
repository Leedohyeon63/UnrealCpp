// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUpConsume_Orb.h"
#include "Player/HasHealth.h"
void APickUpConsume_Orb::OnConsume()
{
	Super::OnConsume();

	if (PickupOwner.IsValid() && PickupOwner->Implements<UHasHealth>())
	{
		IHasHealth::Execute_HealHP(PickupOwner.Get(), HealAmount);
	}
}
