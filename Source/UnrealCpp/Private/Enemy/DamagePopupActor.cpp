// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DamagePopupActor.h"
#include "DamgeWidget.h"
#include "Components/WidgetComponent.h"
#include "Frame/DamagePopupSubsystem.h"

// Sets default values
ADamagePopupActor::ADamagePopupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DamageWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidgetComponent"));
	SetRootComponent(DamageWidgetComponent);

	DamageWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	DamageWidgetComponent->SetDrawAtDesiredSize(true);
}

void ADamagePopupActor::PopupActivate(float Damage)
{
	//UE_LOG(LogTemp, Log, TEXT("PopupActivate"));
	if (DamageWidget)
	{
		//UE_LOG(LogTemp, Log, TEXT("PopupActivate : DamageWidget vaild."));
		DamageWidget->SetDamageText(Damage);
		DamageWidget->PlayPopupAnimation();
	}

	GetWorldTimerManager().SetTimer(
		LifeTimerHandle,
		this,
		&ADamagePopupActor::PopupDeactivate,
		LifeTime,
		false
	);


}

void ADamagePopupActor::PopupDeactivate()
{
	if (UWorld* world = GetWorld())
	{
		if (UDamagePopupSubsystem* PoolSystem = world->GetSubsystem<UDamagePopupSubsystem>())
		{
			PoolSystem->ReturnToPool(this);
		}
		else
		{
			Destroy();	// 안전 장치 : 만약을 대비한 것
		}
	}
	else
	{
		Destroy();	// 안전 장치 : 만약을 대비한 것
	}
}

// Called when the game starts or when spawned
void ADamagePopupActor::BeginPlay()
{
	Super::BeginPlay();

	if (DamageWidgetComponent)
	{
		DamageWidget = Cast<UDamgeWidget>(DamageWidgetComponent->GetUserWidgetObject());
	}
}



