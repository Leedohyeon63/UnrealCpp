// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataAsset.h"
#include "Item/Useabel/UseableItem.h"
#include "UseableDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UUseableDataAsset : public UItemDataAsset, public IUseableItem
{
	GENERATED_BODY()
public:
};
