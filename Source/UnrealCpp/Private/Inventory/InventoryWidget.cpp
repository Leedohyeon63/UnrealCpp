// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/InventoryWidget.h"
#include "Inventory/InventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/InventoryComponent.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnCloseClicked);
	}
}


void UInventoryWidget::InitailizeInventoryWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent)
	{
		TargetInventory = InventoryComponent;

		if (TargetInventory.IsValid())
		{
			for (size_t i = 0; i < TargetInventory->GetInventorySize(); i++)
			{
				FInvenSlot* slot = TargetInventory->GetSlotData(i);
			}

			int32 Size = FMath::Min(SlotGridPanel->GetChildrenCount(), TargetInventory->GetInventorySize());
			for (size_t i = 0; i < Size; i++)
			{
				FInvenSlot* SlotData = TargetInventory->GetSlotData(i);
				UInventorySlotWidget* SlotWidget = Cast<UInventorySlotWidget>(SlotGridPanel->GetChildAt(i));
				SlotWidget->InitializeSlot(i, SlotData);
				SlotWidgets.Add(SlotWidget);
			}


		}
	}
}

void UInventoryWidget::RefreshInventory()
{
	for (const UInventorySlotWidget* slot : SlotWidgets)
	{
		slot->RefreshSlot();
	}
}

void UInventoryWidget::ClearInvnetory()
{
	TargetInventory = nullptr;
}

void UInventoryWidget::OnCloseClicked()
{
	OnInventoryCloseRequsted.Broadcast();
}