// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/InventoryComponent.h"
#include "InventorySlotWidget.generated.h"
//struct FInvenSlot;
//class UInventoryComponent;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSlotClicked, int32, InSlotIndex);
/**
 * 
 */
UCLASS()
class UNREALCPP_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitializeSlot(UInventoryComponent* InInventoryComponent, int32 InIndex);
	void RefreshSlot() const;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;

	// 드래그 완료
	virtual bool NativeOnDrop(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	// 드래그 취소
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

public:
	FOnSlotClicked OnSlotRightClick;

protected:
	void ClearSlotWidget() const;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> CountText = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxText = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> SpaerText = nullptr;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
private:
	int32 Index = -1;

	FInvenSlot* SlotData = nullptr;	// 구조체는 TWeakObjectPtr이 인식을 못하는 것 같다.

	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;
};
