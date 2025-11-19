// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ConsumableWeapon.h"

void AConsumableWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentUseCount = MaxUseCount;
}

void AConsumableWeapon::OnWeaponActivate()
{
	CurrentUseCount = MaxUseCount;
}

void AConsumableWeapon::OnAttack()
{
	CurrentUseCount--;
	UE_LOG(LogTemp, Log, TEXT("%d"), CurrentUseCount);
	if (CurrentUseCount <= 0)
	{
		OnWeaponUseEnded.Broadcast(WeaponID);
	}
}

void AConsumableWeapon::OnWeaponPickuped(int InCount)
{
	// 현재 사용되는 곳 없음
	Super::OnWeaponPickuped(InCount);
	CurrentUseCount = InCount;
}
