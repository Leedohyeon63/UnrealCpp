// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/InventoryComponent.h"
#include "ItemSellWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UItemSellWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	// 드래그 완료
	virtual bool NativeOnDrop(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;
	void GetSellGold(AActor* InTarget, int32 Gold);
private:
	int32 Index = -1;

	FInvenSlot* SlotData = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;
};
