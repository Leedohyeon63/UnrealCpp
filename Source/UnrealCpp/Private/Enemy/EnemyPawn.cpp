// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Player/ResourceComponent.h"
#include "Enemy/DamagePopupActor.h"
#include "Frame/DamagePopupSubsystem.h"
#include "Frame/EnemyTrackingSubsystem.h"
#include "Frame/PickupFactorySubsystem.h"
#include "Data/DropItemData_TableRow.h"
#include "Item/PickUp.h"

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
	//GEngine->AddOnScreenDebugMessage()
	if (Resource->IsAlive())
	{
		if (!bInvinciable || !FMath::IsNearlyEqual(LastDamage, Damage))
		{
			UE_LOG(LogTemp, Log, TEXT("Damage : %.1f"), Damage);

			Resource->AddHP(-Damage);
			//ADamagePopupActor* actor = GetWorld()->SpawnActor<ADamagePopupActor>(
			//	DamagePopupClass, PopupLocation->GetComponentToWorld());
			//if (actor)
			//{
			//	actor->PopupActivate(Damage);
			//}

			UDamagePopupSubsystem* popupSystem = GetWorld()->GetSubsystem<UDamagePopupSubsystem>();
			popupSystem->ShowDamagePopup(Damage, PopupLocation->GetComponentLocation());

			if (Resource->IsAlive())
			{
				// 한번에 연속해서 데미지 입는것 방지
				bInvinciable = true;
				LastDamage = Damage;

				FTimerDelegate resetInvincibleDelegate = FTimerDelegate::CreateWeakLambda(
					this,
					[this]()
					{
						bInvinciable = false;
					});	// this가 파괴되면 람다는 더 이상 실행되지 않는다.

				GetWorldTimerManager().ClearTimer(InvinciableTimeer);
				GetWorldTimerManager().SetTimer(
					InvinciableTimeer,
					resetInvincibleDelegate,
					0.1f, false);
			}
			else
			{
				Ondie();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("이 적은 이미 죽어있다."));
	}

}

void AEnemyPawn::DropItems()
{
	APickUp* pickup = nullptr;
	TMap<FName, uint8*> RowMap = DropItemTable->GetRowMap();

	// 중복으로 당첨 가능(아무것도 안나올 수도 있음)
	for (const auto& element : RowMap)
	{
		pickup = nullptr;
		FDropItemData_TableRow2* row = (FDropItemData_TableRow2*)element.Value;
		if (FMath::FRand() <= row->DropRate)
		{
			//pickup = GetWorld()->SpawnActor<APickup>(
			//	row->DropItemClass,
			//	GetActorLocation() + FVector::UpVector * 200.0f,
			//	GetActorRotation());

			pickup = GetWorld()->GetSubsystem<UPickupFactorySubsystem>()->SpawnPickup(
				row->PickupCode,
				GetActorLocation() + FVector::UpVector * 200.0f,
				GetActorRotation()
			);
		}
		if (pickup)
		{
			UE_LOG(LogTemp, Log, TEXT("Drop Success : %s"), *pickup->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Drop empty"));
		}
	}
		//float TotalWeight = 0.0f;
		//for (auto& elenment : RowMap)
		//{
		//	FDropItemData_TableRow* Row = (FDropItemData_TableRow*)elenment.Value;
		//	TotalWeight += Row->DropRate;
		//}
		//float RandomSelect = FMath::FRandRange(0, TotalWeight);
		//float CurrentWeight = 0.0f;
		//for (auto& elenment : RowMap)
		//{
		//	FDropItemData_TableRow* Row = (FDropItemData_TableRow*)elenment.Value;
		//	CurrentWeight += Row->DropRate;
		//	if (RandomSelect < CurrentWeight)
		//	{
		//		//당첨 -> 스폰처리
		//		GetWorld()->SpawnActor<APickUp>(
		//		Row->DropItemClass,
		//		GetActorLocation() + FVector::UpVector * 200.0f,
		//		GetActorRotation());
		//		break;
		//	}
		//}
}

void AEnemyPawn::Ondie()
{
	DropItems();
	Destroy();
}


