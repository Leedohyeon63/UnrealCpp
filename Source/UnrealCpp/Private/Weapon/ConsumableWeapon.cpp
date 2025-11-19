// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ConsumableWeapon.h"

void AConsumableWeapon::OnAttack()
{
	CurrentUseCount--;
	UE_LOG(LogTemp, Log, TEXT("%d"), CurrentUseCount);
	if (CurrentUseCount <= 0)
	{
		OnWeaponUseEnded.Broadcast(WeaponID);
	}
}

void AConsumableWeapon::OnWeaponPickuped()
{
	Super::OnWeaponPickuped();
	CurrentUseCount = MaxUseCount;
}
