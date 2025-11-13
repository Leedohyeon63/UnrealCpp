// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ResourceBarWidget.h"
#include "Components/ProgressBar.h"

void UResourcebarWidget::RefreshWidget(float InCurrent, float InMax)
{
	Bar->SetPercent(InCurrent / InMax);

}

void UResourcebarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	Bar->SetFillColorAndOpacity(FillColor);
}
