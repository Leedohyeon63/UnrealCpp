// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUp.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "NiagaraComponent.h"
#include "Player/InventoryOwner.h"
// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseRoot = CreateDefaultSubobject<USphereComponent>(TEXT("BaseRoot"));
	SetRootComponent(BaseRoot);
	BaseRoot->SetSimulatePhysics(true);
	BaseRoot->InitSphereRadius(1.0f);
	BaseRoot->BodyInstance.bLockXRotation = true;
	BaseRoot->BodyInstance.bLockYRotation = true;
	BaseRoot->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetupAttachment(BaseRoot);
	Mesh->AddRelativeRotation(FRotator(0, 0, -10.0f));

	PickUpOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	PickUpOverlap->SetupAttachment(BaseRoot);
	PickUpOverlap->SetSphereRadius(100.0f);
	PickUpOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Niagara->SetupAttachment(BaseRoot);

	PickUpTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("PickupTimeline"));

}





// Called when the game starts or when spawned
void APickUp::BeginPlay()
{

	Super::BeginPlay();

	bPickuped = false;

	if (PickUpOverlap)
	{
		PickUpOverlap->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnPickUpOverLap);
	}

	if (PickUpTimeline)
	{
		if (ScaleCurve)
		{
			FOnTimelineFloat ScaleUpdateDelegate;
			ScaleUpdateDelegate.BindUFunction(this, FName("OnScaleUpdate"));
			PickUpTimeline->AddInterpFloat(ScaleCurve, ScaleUpdateDelegate);

			FOnTimelineEvent ScaleFinishDelegate;
			ScaleFinishDelegate.BindUFunction(this, FName("OnScaleFinish"));
			PickUpTimeline->SetTimelineFinishedFunc(ScaleFinishDelegate);
		}
	}

	PickUpTimeline->SetPlayRate(1/Duration);
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddWorldRotation(FRotator(0, RotateSpeed* DeltaTime, 0));

}

void APickUp::OnPickUp_Implementation(AActor* Target)
{
	if (!bPickuped)
	{
		bPickuped = true;
		PickupOwner = Target;
		PickUpTimeline->PlayFromStart();
	}
}

void APickUp::OnPickUpOverLap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, const 
	FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("pickup"))
}

void APickUp::OnScaleUpdate(float InValue)
{
	FVector NewScale = FVector::One() * InValue;
	SetActorScale3D(NewScale);
}

void APickUp::OnScaleFinish()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem);
	}
}




