// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "UI/MainHudWidget.h"
#include "ActionPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class UNREALCPP_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn*aPawn) override;
	virtual void OnUnPossess() override;
public:
	virtual void SetupInputComponent() override;
	void InitializeMainHudWidget(UMainHudWidget* Widget);
	void OpenInventoryWidget();
	UFUNCTION()
	void CloseInventoryWidget();

private:
	void OnLookInput(const FInputActionValue& InValue);
	void OnInvnentoryOnOff();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMapping = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_InventoryOnOff = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Pitch")
	float VewPitchMin = -40;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Pitch")
	float VewPitchMax = 30;

private:
	int32 GameInputPriority = 1;
	TWeakObjectPtr<UMainHudWidget> MainHubWidget = nullptr;
	TWeakObjectPtr<UInventoryWidget> InventoryWidget = nullptr;
	TWeakObjectPtr<class UInventoryComponent> InventoryComponent = nullptr;
};
