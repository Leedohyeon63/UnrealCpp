// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ResourcebarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
void UResourcebarWidget::UpdateWidget(float InCurrent, float InMax)
{
	Bar->SetPercent(InCurrent / InMax);
	
}
