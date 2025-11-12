// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourcebarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UResourcebarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateWidget(float InCurrent, float InMax);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UProgressBar> Bar;


};
