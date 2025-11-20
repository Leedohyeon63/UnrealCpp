// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NiagaraTestActor.h"
#include "NiagaraComponent.h"
// Sets default values
ANiagaraTestActor::ANiagaraTestActor()
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
void ANiagaraTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANiagaraTestActor::TestColorChange(FLinearColor& Color)
{
	Effect->SetColorParameter(TEXT("TestCol"), Color);
	//Effect->SetNiagaraVariableLinearColor(TEXT("Col"), Color);


}

// Called every frame
void ANiagaraTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

