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
	HealthPotion UMETA(DisplayName = "체력물약"),
	StaminaPotion UMETA(DisplayName = "스테미나물약"),
	Crown UMETA(DisplayName = "왕관"),
	HPOrb UMETA(DisplayName = "힐링오브"),
	Coin UMETA(DisplayName = "코인"),
	
};

UENUM(BlueprintType)
enum class DamgeType : uint8
{
	Fire UMETA(DisplayName = "화염데미지"),
	Ice UMETA(DisplayName = "얼음데미지"),
	Spark UMETA(DisplayName = "전기데미지"),
};

UENUM(BlueprintType)
enum class EWeaponCode : uint8
{
	BasicWeapon UMETA(DisplayName = "기본무기"),
	DragonSword UMETA(DisplayName = "드래곤소드"),
	HeroSword UMETA(DisplayName = "히어로소드"),
//	HealthPotion UMETA(DisplayName = "물약"),

};