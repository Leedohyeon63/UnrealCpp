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
//UPROPERTY
//Ucalss, UFUNCTION의 멤버 변수를 언리얼 엔진의 리플렉션 시스템에 등록
//에디터에서 노출 및 편집을 가능하게 한다.
//가비지 컬렉션이 추적을 가능하게 함
//직렬화(변수의 값이 레벨이나 에셋에 함께 저장)
//네트워크 복제
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
protected:
	int32 Data1 = 10;

	UPROPERTY(VisibleAnywhere, Category = "Test변수")
	int32 Data2 = 20;

	UPROPERTY(VisibleDefaultsOnly, Category = "Test변수")
	int32 Data3 = 20;

	UPROPERTY(VisibleInstanceOnly, Category = "Test변수")
	int32 Data4 = 20;

	UPROPERTY(BlueprintReadOnly, Category = "Test변수")
	int32 Data5 = 30;

	UPROPERTY(BlueprintReadWrite, Category = "Test변수")
	int32 Data6 = 40;

	UPROPERTY(EditAnywhere, Category = "Test변수")
	int32 Data7 = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Test변수")
	int32 Data8 = 20;

	UPROPERTY(EditInstanceOnly, Category = "Test변수")
	int32 Data9 = 20;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Test변수")
	int32 Data10 = 120;
};
