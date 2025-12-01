// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Player/MainHUD.h"
void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem)
	{
		SubSystem->AddMappingContext(DefaultMapping, GameInputPriority);
	}

	PlayerCameraManager->ViewPitchMax = VewPitchMax;
	PlayerCameraManager->ViewPitchMin = VewPitchMin;
}

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(InputComponent);
	if (enhanced)	// 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		//UE_LOG(LogTemp, Log, TEXT("바인드 성공"));
		enhanced->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AActionPlayerController::OnLookInput);
		enhanced->BindAction(IA_InventoryOnOff, ETriggerEvent::Started, this, &AActionPlayerController::OnInvnentoryOnOff);
	}
}

void AActionPlayerController::OnLookInput(const FInputActionValue& InValue)
{
	FVector2D lookAxis = InValue.Get<FVector2D>();
	//UE_LOG(LogTemp, Log, TEXT("OnLookInput : %s"), *lookAxis.ToString());
	AddYawInput(lookAxis.X);
	AddPitchInput(lookAxis.Y);
}

void AActionPlayerController::OnInvnentoryOnOff()
{
	if (MainHubWidget.IsValid())
	{
		if (MainHubWidget->GetOpenState() == EOpenState::Open)
		{
			CloseInventoryWidget();
		}
		else
		{
			OpenInventoryWidget();
		}
	}
}

void AActionPlayerController::OpenInventoryWidget()
{
	if (MainHubWidget.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("OpenInventoryWidget"));
		MainHubWidget->OpenInventory();
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(MainHubWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
		bShowMouseCursor = true;
		//SetIgnoreLookInput(true);
		//SetIgnoreMoveInput(true);
		SetPause(true);
	}
}

void AActionPlayerController::CloseInventoryWidget()
{
	if (MainHubWidget.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("CloseInventoryWidget"));
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		SetPause(false);
		bShowMouseCursor = false;
		//SetIgnoreLookInput(false);
		//SetIgnoreMoveInput(false);
		MainHubWidget->CloseInventory();
	}
}
