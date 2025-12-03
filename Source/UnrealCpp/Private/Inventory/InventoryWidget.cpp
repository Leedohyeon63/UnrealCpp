// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/InventoryWidget.h"
#include "Inventory/InventorySlotWidget.h"
#include "Inventory/GoldPannalWidget.h"
#include "UI/IventoryDragDropOperation.h"
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
	if (InventoryComponent && SlotGridPanel)
	{
		TargetInventory = InventoryComponent;	// 인벤토리 컴포넌트 저장
		if (TargetInventory.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("인벤토리 위젯 초기화"));

			if (SlotGridPanel->GetChildrenCount() != TargetInventory->GetInventorySize())
			{
				UE_LOG(LogTemp, Error, TEXT("인벤토리 컴포넌트와 위젯의 슬롯 크기가 다릅니다!!!"));
				return;
			}

			TargetInventory->OnInventorySlotChanged.BindUFunction(this, "RefreshSlotWidget");
			TargetInventory->OnInventoryMoneyChanged.BindUFunction(this, "RefreshMoneyPanel");

			RefreshMoneyPanel(0);
			int32 size = FMath::Min(SlotGridPanel->GetChildrenCount(), TargetInventory->GetInventorySize());
			SlotWidgets.Empty(size);
			for (int i = 0; i < size; i++)
			{
				// 인벤토리 컴포넌트에 저장되어있는 슬롯과 슬롯 위젯을 엮어주는 작업
				UInventorySlotWidget* slotWidget = Cast<UInventorySlotWidget>(SlotGridPanel->GetChildAt(i));
				slotWidget->InitializeSlot(TargetInventory.Get(), i);

				SlotWidgets.Add(slotWidget);	// 연결이 끝난 슬롯을 SlotWidgets에 순서대로 저장
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

void UInventoryWidget::RefreshSlotWidget(int32 InSlotIndex)
{
	if (IsValidIndex(InSlotIndex))
	{
		SlotWidgets[InSlotIndex]->RefreshSlot();
	}
}

void UInventoryWidget::RefreshMoneyPanel(int32 CurrentMoney)
{
	GoldPannal->SetGold(CurrentMoney);
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		UE_LOG(LogTemp, Log, TEXT("인벤토리에 드랍 : 원래 슬롯(%d)으로 아이템이 돌아가야 한다."), invenOp->Index);
		return true;
	}
	return false;
}
