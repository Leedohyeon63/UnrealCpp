// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemBuyWidget.generated.h"
class UImage;
class UTextBlock;
class UButton;
class UEditableTextBox;
class UOverlay;
/**
 * 
 */
UCLASS()
class UNREALCPP_API UItemBuyWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
	void OnItemCountTextChanged(const FText& Text);
	UFUNCTION()
	void OnItemCountTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPrice;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemSkockCount;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDiscripsion;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ItemCount;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UButton> ItemBuy;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSet", meta = (BindWidget))
	TObjectPtr<UOverlay> Soldout;
};
