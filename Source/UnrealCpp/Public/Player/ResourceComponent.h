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
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddStamina(float InValue);

	// 스태미너가 충분한지 확인하는 함수
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool HasEnoughStamina(float InValue) { return Stamina >= InValue; }

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaEmpty OnStaminaEmpty;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxStamina = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Stamina = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float StaminaInProve = 7.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float StaminaCoolDown = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float StaminaTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaTickInterval = 0.1f;

	FTimerHandle StaminaAutoRegenCoolTimer;	// 스태미너 자동 회복용 타이머 핸들
	FTimerHandle StaminaRegenTickTimer;
};
