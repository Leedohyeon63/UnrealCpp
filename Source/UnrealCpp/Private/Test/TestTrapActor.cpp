// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestTrapActor.h"
#include "Common/CommonEnum.h"
#include "NiagaraComponent.h"

// Sets default values
ATestTrapActor::ATestTrapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROOT"));
	SetRootComponent(Root);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Effect->SetupAttachment(Root);
	Effect->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));



}

// Called when the game starts or when spawned
void ATestTrapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestTrapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

