// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventorySlotWidget.h"
#include "UI/IventoryDragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/InventoryComponent.h"
#include "Inventory/TemporarySlotWidget.h"
#include "string.h"
void UInventorySlotWidget::InitializeSlot(UInventoryComponent* InInventoryComponent, int32 InIndex)
{
	if (InInventoryComponent)
	{
		TargetInventory = InInventoryComponent;
		Index = InIndex;
		SlotData = TargetInventory->GetSlotData(InIndex);
		OnSlotRightClick.BindUFunction(TargetInventory.Get(), "UseItem");	// 인벤토리 컴포넌트에 있는 UseItem과 바인딩
		RefreshSlot();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InInventoryComponent가 nullptr입니다!!!"));
	}
}

void UInventorySlotWidget::RefreshSlot() const
{
	if (SlotData && !SlotData->IsEmpty())
	{
		ItemIconImage->SetBrushFromTexture(SlotData->ItemData->ItemIcon);
		ItemIconImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		CountText->SetText(FText::AsNumber(SlotData->GetCount()));
		MaxText->SetText(FText::AsNumber(SlotData->ItemData->ItemMaxStackCount));

		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		MaxText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SpaerText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		ClearSlotWidget();
	}
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	UE_LOG(LogTemp, Log, TEXT("DragDetected : %d Slot"), this->Index);

	UIventoryDragDropOperation* DragOp = NewObject<UIventoryDragDropOperation>();

	// 기본 데이터 세팅
	DragOp->Index = Index;
	DragOp->ItemData = SlotData->ItemData;
	DragOp->Count = SlotData->GetCount();

	// 비주얼 위젯 만들기
	UTemporarySlotWidget* DragTemporaryWidget = CreateWidget<UTemporarySlotWidget>(
		this, TargetInventory->GetTemporarySlotWidgetClass());
	DragTemporaryWidget->SetItemIconImage(SlotData->ItemData->ItemIcon);
	DragTemporaryWidget->SetCountText(SlotData->GetCount());

	DragOp->DefaultDragVisual = DragTemporaryWidget;


	OutOperation = DragOp;	// NativeOnDrop나 NativeOnDragCancelled를 발동시키기 위해 반드시 필요

	TargetInventory->ClearSlotAtIndex(Index);
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		UE_LOG(LogTemp, Log, TEXT("Drop : %d Slot에 %s를 옮기기"),
			Index,
			*(invenOp->ItemData->ItemName.ToString()));

		TargetInventory->SetItemAtIndex(Index, invenOp->ItemData.Get(), invenOp->Count);

		return true;	// 성공적으로 끝났음을 알림
	}
	return false;		// 실패로 끝났음을 알림 -> NativeOnDragCancelled 실행
}

void UInventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		UE_LOG(LogTemp, Log,
			TEXT("DragCancelled : 바닥에다가 (%s)아이템을 버려야 한다."),
			*(invenOp->ItemData->ItemName.ToString()));


	}
}

void UInventorySlotWidget::ClearSlotWidget() const
{
	ItemIconImage->SetBrushFromTexture(nullptr);
	ItemIconImage->SetBrushTintColor(FLinearColor::Transparent);
	CountText->SetVisibility(ESlateVisibility::Hidden);
	MaxText->SetVisibility(ESlateVisibility::Hidden);
	SpaerText->SetVisibility(ESlateVisibility::Hidden);

}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (!SlotData->IsEmpty())
		{
			UE_LOG(LogTemp, Log, TEXT("index : %d, ItemData : %s"), Index, *SlotData->ItemData->ItemName.ToString());
			OnSlotRightClick.ExecuteIfBound(Index);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Empty"));
		}
		return FReply::Handled();
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if (SlotData->ItemData)
		{
			return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		}
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
