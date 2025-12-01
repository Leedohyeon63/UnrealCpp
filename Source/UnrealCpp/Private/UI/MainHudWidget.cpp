// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHudWidget.h"
#include "Player/ActionCharacter.h"
#include "Player/ResourceComponent.h"
#include "UI/ResourceBarWidget.h"


void UMainHudWidget::NativeConstruct()
{
	AActionCharacter* player = Cast<AActionCharacter>(GetOwningPlayerPawn());
	CloseInventory();

	if (player)
	{

		if (UResourceComponent* resource = player->GetResourceComponent())
		{
			resource->OnHPChange.AddUObject(HPBar.Get(), &UResourcebarWidget::RefreshWidget);
			resource->OnStaminaChange.AddDynamic(StaminaBar.Get(), &UResourcebarWidget::RefreshWidget);

			HPBar->RefreshWidget(resource->GetCurrentHealth(), resource->GetMaxHealth());
			StaminaBar->RefreshWidget(resource->GetCurrentStamina(), resource->GetMaxStamina());
		}

		if (UInventoryComponent* InventoryComponent = player->GetInventoryComponent())
		{
			//Inventory->OnInventoryCloseRequsted.AddDynamic(this, &UMainHudWidget::CloseInventory);
			
		}
	}


}

void UMainHudWidget::OpenInventory()
{
	Inventory->RefreshInventory();
	Inventory->SetVisibility(ESlateVisibility::Visible);
	OpenState = EOpenState::Open;
}

void UMainHudWidget::CloseInventory()
{
	Inventory->SetVisibility(ESlateVisibility::Hidden);
	OpenState = EOpenState::Close;

}
