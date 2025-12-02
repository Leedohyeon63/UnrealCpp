// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Useabel/UseableDataAsset.h"
#include "HPPostionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UHPPostionDataAsset : public UUseableDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData|HPpotion")
	float HealAmount = 30.0f;

public:
	virtual void UseItem_Implementation(AActor* InTarget) override;
	
};
