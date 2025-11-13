// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ResourceComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentHealth(MaxHP);
	SetCurrentStamina(MaxStamina);
	// ...
	
}

void UResourceComponent::StaminaAutoRegenCoolTimerSet()
{
	UWorld* world = GetWorld();
	FTimerManager& timerManager = world->GetTimerManager();

	//GetWorldTimerManager().ClearTimer(StaminaCoolTimer);	// 해서 나쁠 것은 없음(SetTimer할 때 이미 내부적으로 처리하고 있다)
	timerManager.ClearTimer(StaminaRegenTickTimer);
	timerManager.SetTimer(
		StaminaAutoRegenCoolTimer,
		[this]() {
			//bRegenStamina = true;
			UE_LOG(LogTemp, Log, TEXT("리젠 타이머 실행"));

			UWorld* world = GetWorld();
			FTimerManager& timerManager = world->GetTimerManager();
			timerManager.SetTimer(
				StaminaRegenTickTimer,
				this,
				&UResourceComponent::StaminaRegenPerTick,
				StaminaTickInterval,	// 실행 간격
				true,	// 반복 재생 여부
				StaminaTickInterval);	// 첫 딜레이
		},
		StaminaCoolDown,
		false);
}

void UResourceComponent::StaminaRegenPerTick()
{
	Stamina += StaminaInProve;
	
	if (Stamina > MaxStamina)
	{
		Stamina = MaxStamina;
		UWorld* world = GetWorld();
		FTimerManager& timerManager = world->GetTimerManager();
		timerManager.ClearTimer(StaminaRegenTickTimer);
	}

	UE_LOG(LogTemp, Warning, TEXT("Stamina Regen : %.1f"), Stamina);
}


// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResourceComponent::AddStamina(float InValue)
{
	//TimeSinceLastStaminaUse = 0;	// 시간을 직접 제어할 때 쓰던 코드(예시 확인용)
	SetCurrentStamina(FMath::Clamp(Stamina + InValue, 0, MaxStamina));
	// 스태미너를 소비하고 일정 시간 뒤에 자동재생되게 타이머 세팅

	if (InValue < 0)
	{
		StaminaAutoRegenCoolTimerSet();

	}
	if (Stamina <= 0)
	{
		Stamina = 0.0f;
		// 델리게이트로 스태미너가 떨어졌음을 알림
		OnStaminaEmpty.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("Stamina : %.1f"), Stamina);
}

void UResourceComponent::AddHP(float InValue)
{

	float HP = CurrentHP + InValue;
	SetCurrentHealth(FMath::Clamp(HP, 0, MaxHP));

	if (!IsAlive())
	{
		OnDie.Broadcast();
	}
}

