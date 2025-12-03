// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Shop/ItemBuyWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Data/ItemDataAsset.h"
#include "Player/InventoryOwner.h"

void UItemBuyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ItemCount)
	{
		ItemCount->OnTextChanged;
		ItemCount->OnTextCommitted;


	}




}

void UItemBuyWidget::OnItemCountTextChanged(const FText& Text)
{
}

void UItemBuyWidget::OnItemCountTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
}
