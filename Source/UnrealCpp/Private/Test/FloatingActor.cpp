// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	CurrrentHeight = BodyMesh->GetRelativeLocation();


	//BodyMesh->SetRelativeLocation(FVector(0,0,100));

}

void AFloatingActor::OnFloatingMeshUpdate(float DeltaTime)
{
	rad += DeltaTime;
	float Cosine = (FMath::Cos(rad) + 1) * 0.5f;
	Cosine = 1 - Cosine;
	BodyMesh->AddRelativeRotation(FRotator(0, DeltaTime * SpinSpeed, 0));
	BodyMesh->SetRelativeLocation(FVector(CurrrentHeight.X, CurrrentHeight.Y, CurrrentHeight.Z + Cosine * MoveHeight));
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//rad += DeltaTime;
	//float Cosine = (FMath::Cos(rad) + 1) * 0.5f;
	//Cosine = 1 - Cosine;
	//BodyMesh->AddRelativeRotation(FRotator(0, DeltaTime*SpinSpeed,0));
	//BodyMesh->SetRelativeLocation(FVector(CurrrentHeight.X, CurrrentHeight.Y, CurrrentHeight.Z + Cosine*MoveHeight));
	//UE_LOG(LogTemp, Log, TEXT("%f"),Cosine);
	OnFloatingMeshUpdate(DeltaTime);
}

