// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WeaponActor.h"
#include "Components//CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetupAttachment(root);
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	WeaponCollision->SetupAttachment(WeaponMesh);
	WeaponCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AWeaponActor::OnWeaponBeginOverlap);
}

void AWeaponActor::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	float FinalDamage = Damage;
	AController* instigator = nullptr;
	if (WeaponOwner.IsValid())
	{
		if (WeaponOwner == OtherActor)
		{
			return;
		}
		//FinalDamage += WeaponOwner->GetattackPower();
		instigator = WeaponOwner->GetController();
	}
	UE_LOG(LogTemp, Log, TEXT("OverLapped : %s"), *OtherActor->GetName());

	UGameplayStatics::ApplyDamage(OtherActor, FinalDamage, instigator, this, DamageType);
}


// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::AttackEnable(bool bEnable)
{
	if (bEnable)
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeaponActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

