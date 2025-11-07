// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();//부모 클래스의 beginplay를 실행
	UE_LOG(LogTemp, Log, TEXT("Hello 한글도 가능") );
	UE_LOG(LogTemp, Warning, TEXT("Hello 한글도 가능"));
	UE_LOG(LogTemp, Error, TEXT("Hello 한글도 가능") );
}

void ATestActor::Test_NativeFunctoin_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("NativeFuntion호출"));

}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::Testnormal()
{
	UE_LOG(LogTemp, Log, TEXT("Normal호출"));

}

void ATestActor::Test_UFunction()
{
	UE_LOG(LogTemp, Log, TEXT("UFuntion호출"));

}

