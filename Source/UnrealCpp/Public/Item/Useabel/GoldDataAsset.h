// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Useabel/UseableDataAsset.h"
#include "GoldDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UGoldDataAsset : public UUseableDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData|Gold")
	int32 GoldMin = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData|Gold")
	int32 GoldMax = 1000;
public:
	virtual void UseItem_Implementation(AActor* InTarget) override;
};
