// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//generated 헤더는 모든 헤더 중 가장 마지막에 있어야 함
#include "TestActor.generated.h"
//Ucalss
//c++클래스를 언리얼 엔진에 객체 시스템에 등록
//UFUNCTION
//블루프린트에서 함수를 호출, 구현, 재정의 등을 할 때 사용
//델리게이트에 바인딩 할 경우 
UCLASS()
class UNREALCPP_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Testnormal();
	UFUNCTION(BlueprintCallable, Category = "Function")
	void Test_UFunction();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Function")
	void Test_ImplementableFunctoin();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Function")
	void Test_NativeFunctoin();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
