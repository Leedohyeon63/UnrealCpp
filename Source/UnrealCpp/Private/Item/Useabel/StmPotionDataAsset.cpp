// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Useabel/StmPotionDataAsset.h"
#include "Player/HasStamina.h"	

void UStmPotionDataAsset::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UHasStamina>())
	{
		IHasStamina::Execute_HealSTM(InTarget, StaminaAmount);
	}
}
