// Fill out your copyright notice in the Description page of Project Settings.


#include "DamgeWidget.h"
#include "Components/TextBlock.h"

void UDamgeWidget::SetDamageText(float Damage)
{
	if (DamageText)
	{
		DamageText->SetText(FText::AsNumber(static_cast<int32>(Damage)));
	}
}

void UDamgeWidget::PlayPopupAnimation()
{
	if (PopupAnimation)
	{
		PlayAnimation(PopupAnimation, 0, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}
