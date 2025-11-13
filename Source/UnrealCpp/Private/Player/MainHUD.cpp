// Fill out your copyright notice in the Description page of Pro
// 
// ject Settings.


#include "Player/MainHUD.h"
#include "Blueprint/UserWidget.h"


void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MainWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}

}
