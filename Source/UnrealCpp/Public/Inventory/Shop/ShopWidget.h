// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop|Buy")
	TWeakObjectPtr<UDataTable> ShopItemList = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop|Buy", meta = (ItemBuyList))

protected:
	void SetProductList();
};
