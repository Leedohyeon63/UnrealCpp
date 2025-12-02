// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Useabel/UseableDataAsset.h"
#include "StmPotionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UStmPotionDataAsset : public UUseableDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData|STMpotion")
	float StaminaAmount = 100.0f;

public:
	virtual void UseItem_Implementation(AActor* InTarget) override;
};
