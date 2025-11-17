// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)

enum class EItemCode : uint8
{
	BasicWeapon UMETA(DisplayName = "기본무기"),
	DragonSword UMETA(DisplayName = "드래곤소드"),
	HeroSword UMETA(DisplayName = "히어로소드"),
	
};