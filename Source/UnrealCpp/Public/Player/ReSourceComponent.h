// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"

//DELEGATE
//그냥 delegate vs dynamic delegate
// dynamic delegate는 블루프린트에서 사용 가능
// dynamic delegate는 일반 delegate보다 느리다
// dynamic delegate에는 람다식 추가가 불가능
// dynamic delegate에 바인딩 되는 함수는 UFUNTION으로 선언해야 함
//그냥 delegate vs multicast delegate
// multicast delegate는 여러 리스너를 바인딩 할 수 있다.
//그냥 delegate vs Event
// event는 외부에서 바인딩만 가능
// delegate는 외부에서 바인딩과 실행 모두 가능
//선언은 클래스 외부에서 선언

//선언은 서로 조합이 가능하다
//DECLARE_DELEGATE
//DECLARE_DYNAMIC_DELEGATE
//DECLARE_MULTICAST_DELEGATE
//DECLARE_DYNAMIC_MULTICAST_DELEGATE
//DECLARE_DELEGATE_RetVal
//DECLARE_DELEGATE_EightParams
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaEmpty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChange, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChange, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPP_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	void StaminaAutoRegenCoolTimerSet();
	void StaminaRegenPerTick();

	inline void SetCurrentHealth(float InValue) {
		CurrentHP = InValue;
		OnHPChange.Broadcast(CurrentHP, MaxHP);
	};
	inline void SetCurrentStamina(float InValue) {
		Stamina = InValue;
		OnHPChange.Broadcast(Stamina, MaxStamina);
	};
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddStamina(float InValue);

	UFUNCTION(BlueprintCallable)
	void AddHP(float InValue);

	// 스태미너가 충분한지 확인하는 함수
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool HasEnoughStamina(float InValue) { return Stamina >= InValue; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool IsAlive() { return CurrentHP > 0; }

	inline float GetCurrentHealth() const { return CurrentHP; }
	inline float GetMaxHealth() const { return MaxHP; }
	inline float GetCurrentStamina() const { return Stamina; }
	inline float GetMaxStamina() const { return MaxStamina; }

	//델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaEmpty OnStaminaEmpty;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnDie OnDie;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaChange OnStaminaChange;

	//일반 델리게이트는 일반 블루프린트에서 사용 불가
	FOnHPChange OnHPChange;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CurrentHP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxStamina = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Stamina = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float StaminaInProve = 0.7f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float StaminaCoolDown = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float StaminaTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaTickInterval = 0.1f;

	FTimerHandle StaminaAutoRegenCoolTimer;	// 스태미너 자동 회복용 타이머 핸들
	FTimerHandle StaminaRegenTickTimer;
};
