// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/InventoryComponent.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeSlot(UInventoryComponent* InInventoryComponent, int32 InIndex);
	void RefreshSlot() const;
	void ClearSlot() const;

protected:
	void ClearSlotWidget() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UImage> ItemImage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemName = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemInfo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemPrice = nullptr;

private:
	int32 Index = -1;

	FInvenSlot* SlotData = nullptr;	// 구조체는 TWeakObjectPtr이 인식을 못하는 것 같다.

	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;
};
