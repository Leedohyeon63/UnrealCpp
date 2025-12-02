// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Useabel/HPPostionDataAsset.h"
#include "Player/HasHealth.h"	

void UHPPostionDataAsset::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UHasHealth>())
	{
		IHasHealth::Execute_HealHP(InTarget, HealAmount);
	}
}
