// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UMainHudWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	// meta = (BindWidget) 위젯 블루프린트하고 이 클래스의 변수를 바인드 하겠다
	//위젯 블루프린트의 변수명과 이 클래스의 변수명이 반드시 같아야 한다 대소문자 포함
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourcebarWidget> HPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourcebarWidget> StaminaBar;
};
