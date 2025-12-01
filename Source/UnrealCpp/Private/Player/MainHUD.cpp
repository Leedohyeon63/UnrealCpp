// Fill out your copyright notice in the Description page of Pro
// 
// ject Settings.


#include "Player/MainHUD.h"
#include "Player/ActionPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MainWidgetClass)
	{
		MainWidgetInstanse = CreateWidget<UMainHudWidget>(GetWorld(), MainWidgetClass);
		if (MainWidgetInstanse)
		{
			AActionPlayerController* Pc = Cast<AActionPlayerController>(GetOwningPlayerController());
			MainWidgetInstanse->AddToViewport();
			if (Pc)
			{
				Pc->InitializeMainHudWidget(MainWidgetInstanse);
			}
		}
	}

}
