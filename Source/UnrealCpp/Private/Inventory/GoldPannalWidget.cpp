// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GoldPannalWidget.h"

void UGoldPannalWidget::SetGold(int32 InGold)
{
	GoldText->SetText(FText::AsCurrency(InGold));
}