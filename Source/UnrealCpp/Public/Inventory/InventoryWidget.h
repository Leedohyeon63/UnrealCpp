// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInvnetoryCloseRequested);
/**
 * 
 */
UCLASS()
class UNREALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual	void NativeConstruct() override;
	UPROPERTY(BlueprintAssignable, Category = "UI|Inventory")
	FOnInvnetoryCloseRequested OnInventoryCloseRequsted;

	void InitailizeInventoryWidget(class UInventoryComponent* InventoryComponent);
	void RefreshInventory();
	void ClearInvnetory();
private:
	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION()
	void RefreshSlotWidget(int32 InSlotIndex);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton = nullptr;

	UFUNCTION()
	void RefreshMoneyPanel(int32 CurrentMoney);

	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	inline bool IsValidIndex(int32 InSlotIndex) const {
		return InSlotIndex < SlotWidgets.Num() && InSlotIndex >= 0;
	};

private:
	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> SlotGridPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UGoldPannalWidget> GoldPannal= nullptr;

	TArray<TObjectPtr<class UInventorySlotWidget>> SlotWidgets;
};
