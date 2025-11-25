// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/EnemyTrackingSubsystem.h"

void UEnemyTrackingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentEnemyCount = 0;
	UE_LOG(LogTemp, Log, TEXT("Initi"));

}

void UEnemyTrackingSubsystem::RegistEnemy()
{
	CurrentEnemyCount++;
	OnEnemyCountChanged.Broadcast(CurrentEnemyCount);
}

void UEnemyTrackingSubsystem::UnRegistEnemy()
{
	if (CurrentEnemyCount > 0)
	{
		CurrentEnemyCount--;
		OnEnemyCountChanged.Broadcast(CurrentEnemyCount);
	}

	if (CurrentEnemyCount <= 0)
	{
		OnAllEnemyClear.Broadcast();
	}
}
