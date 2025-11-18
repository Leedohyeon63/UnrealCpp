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
			FOnTimelineFloat UpdateDelegate;
			UpdateDelegate.BindUFunction(this, FName("OnTimelineUpdate"));
			PickUpTimeline->AddInterpFloat(DistanceCurve, UpdateDelegate);

			FOnTimelineEvent FinishDelegate;
			FinishDelegate.BindUFunction(this, FName("OnTimelineFinish"));
			PickUpTimeline->SetTimelineFinishedFunc(FinishDelegate);
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
		PickupStartLocation = Mesh->GetRelativeLocation() + GetActorLocation();//메시의 월드 위치

		SetActorEnableCollision(false);
		BaseRoot->SetSimulatePhysics(false);
		PickUpTimeline->PlayFromStart();

	}
}

void APickUp::OnPickUpOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APickUp::OnTimelineUpdate(float InValue)
{
	//타임라인 진행 시간
	float CurrentTime = PickUpTimeline->GetPlaybackPosition();
	//UE_LOG(LogTemp, Log, TEXT("Timeline : %.2f"), CurrentTime);

	//현재 커브 값 받아오기
	float DistanceValue = InValue;
	float HeightValue = HeightCurve? HeightCurve->GetFloatValue(CurrentTime) : 0.0f;
	float ScaleValue = ScaleCurve ? ScaleCurve->GetFloatValue(CurrentTime) : 1.0f;

	//UE_LOG(LogTemp, Log, TEXT("DistanceValue : %.2f"), DistanceValue);
	//UE_LOG(LogTemp, Log, TEXT("DistanceValue : %.2f"), DistanceValue);
	UE_LOG(LogTemp, Log, TEXT("ScaleValue : %.2f"), ScaleValue);

	//커브 값을 기준으로 새 위치와 스케일 계산
	FVector NewLocation = FMath::Lerp(PickupStartLocation, PickupOwner.Get()->GetActorLocation(), DistanceValue);
	NewLocation += HeightValue* PickupHeight* FVector::UpVector;

	Mesh->SetWorldLocation(NewLocation);

	FVector NewScale = FVector::One() * ScaleValue;
	Mesh->SetRelativeScale3D(NewScale);
}

void APickUp::OnTimelineFinish()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem);
	}
	Destroy();

}




