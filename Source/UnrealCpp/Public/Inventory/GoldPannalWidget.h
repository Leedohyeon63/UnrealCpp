// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoldPannalWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UGoldPannalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetGold(int32 InGold);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> GoldText = nullptr;
};
