// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Player/ResourceComponent.h"
#include "Enemy/DamagePopupActor.h"
#include "Frame/DamagePopupSubsystem.h"
#include "Frame/EnemyTrackingSubsystem.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	PopupLocation = CreateDefaultSubobject<USceneComponent>(TEXT("PopupLocation"));
	PopupLocation->SetupAttachment(Mesh);
	PopupLocation->SetRelativeLocation(FVector(0, 0, 100));

	Resource = CreateDefaultSubobject<UResourceComponent>(TEXT("Resource"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AEnemyPawn::OnTakeDamage);
	if (UWorld* World = GetWorld())
	{
		if (UEnemyTrackingSubsystem* EnemyTracker = World->GetSubsystem<UEnemyTrackingSubsystem>())
		{
			EnemyTracker->RegistEnemy();
		}
	}
}

void AEnemyPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UWorld* World = GetWorld())
	{
		if (UEnemyTrackingSubsystem* EnemyTracker = World->GetSubsystem<UEnemyTrackingSubsystem>())
		{
			EnemyTracker->UnRegistEnemy();
		}
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage()
	UE_LOG(LogTemp, Log, TEXT("Damage : %.1f"), Damage);
	if (Resource->IsAlive())
	{
		if (!bInvinciable || !FMath::IsNearlyEqual(LastDamage, Damage))
		{
			UDamagePopupSubsystem* popupSystem = GetWorld()->GetSubsystem<UDamagePopupSubsystem>();
			popupSystem->ShowDamagePopup(Damage, PopupLocation->GetComponentLocation());

			if (Resource)
			{
				Resource->AddHP(-Damage);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s: Resource component is null when taking damage"), *GetName());
			}
		}
		else
		{
			bInvinciable = true;
			LastDamage = Damage;

			FTimerDelegate ResetDelegate = FTimerDelegate::CreateWeakLambda(this, [this]() {
				bInvinciable = false;
				});

			GetWorldTimerManager().ClearTimer(InvinciableTimeer);
			GetWorldTimerManager().SetTimer(
				InvinciableTimeer,
				ResetDelegate,
				0.2f, false
			); //this가 파괴되면 람다는 더 실행되지 않는다.
		}
	}
	else
	{
		Ondie();
		//UE_LOG(LogTemp, Log, TEXT("이미죽음"));
	}
	//ADamagePopupActor* actor = GetWorld()->SpawnActor<ADamagePopupActor>(
	//	DamagePopupClass, PopupLocation->GetComponentToWorld());
	//if (actor)
	//{
	//	actor->PopupActivate(Damage);
	//}

}

void AEnemyPawn::Ondie()
{
	Destroy();
}


