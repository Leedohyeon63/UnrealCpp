// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Shop/ItemSellWidget.h"
#include "UI/IventoryDragDropOperation.h"
#include "Player/InventoryOwner.h"
bool UItemSellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UIventoryDragDropOperation* invenOp = Cast<UIventoryDragDropOperation>(InOperation);
	if (invenOp && invenOp->ItemData.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Drop : %s 판매"), *(invenOp->ItemData->ItemName.ToString()));
		int32 Gold = (invenOp->ItemData->ItemPrice * invenOp->Count)/2;
		GetSellGold(GetOwningPlayerPawn(), Gold);
		return true;	// 성공적으로 끝났음을 알림


	}
	return false;
}

void UItemSellWidget::GetSellGold(AActor* InTarget, int32 Gold)
{
	if (InTarget->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddMoney(InTarget, Gold);
	}

}
