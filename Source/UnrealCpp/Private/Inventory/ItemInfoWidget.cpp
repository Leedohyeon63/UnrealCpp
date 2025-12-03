// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemInfoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemInfoWidget::InitializeSlot(UInventoryComponent* InInventoryComponent, int32 InIndex)
{
	if (InInventoryComponent)
	{
		TargetInventory = InInventoryComponent;
		Index = InIndex;
		SlotData = TargetInventory->GetSlotData(InIndex);
		RefreshSlot();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InInventoryComponent가 nullptr입니다!!!"));
	}
}

void UItemInfoWidget::RefreshSlot() const
{
	if (SlotData && !SlotData->IsEmpty())
	{
		ItemImage->SetBrushFromTexture(SlotData->ItemData->ItemIcon);
		ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		ItemName->SetText(FText::FromString(SlotData->ItemData->ItemName.ToString()));
		ItemName->SetText(FText::FromString(SlotData->ItemData->ItemDescription.ToString()));
		ItemPrice->SetText(FText::AsNumber(SlotData->ItemData->ItemPrice));

		ItemName->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemPrice->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		ClearSlotWidget();
	}
}

void UItemInfoWidget::ClearSlot() const
{
	ClearSlotWidget();
}

void UItemInfoWidget::ClearSlotWidget() const
{
	ItemImage->SetBrushFromTexture(nullptr);
	ItemImage->SetBrushTintColor(FLinearColor::Transparent);
	ItemName->SetVisibility(ESlateVisibility::Hidden);
	ItemInfo->SetVisibility(ESlateVisibility::Hidden);
	ItemPrice->SetVisibility(ESlateVisibility::Hidden);

}