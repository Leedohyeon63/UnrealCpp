// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IEquipable.h"
#include "NiagaraComponent.h"
#include "Common/CommonEnum.h"
#include "PickUp.generated.h"

UCLASS()
class UNREALCPP_API APickUp : public AActor, public IIEquipable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnPickUp_Implementation(AActor* Target) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USphereComponent> PickUpOverlap = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UNiagaraComponent> Niagara = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USphereComponent> BaseRoot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UTimelineComponent> PickUpTimeline = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	float RotateSpeed = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
	EItemCode PickupItem = EItemCode::BasicWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
	TObjectPtr<UCurveFloat> ScaleCurve = nullptr;//스케일 커브

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
	TObjectPtr<UCurveFloat> DistanceCurve = nullptr;//거리 보간 커브

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
	TObjectPtr<UCurveFloat> HeightCurve = nullptr;//높이 커브

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	float PickupHeight = 0.5f;

private:
	UFUNCTION()
	void OnPickUpOverLap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTimelineUpdate(float InValue);

	UFUNCTION()
	void OnTimelineFinish();

private:
	TWeakObjectPtr<AActor> PickupOwner = nullptr;

	bool bPickuped = false;
	//획득했을 때 메시 위치
	FVector PickupStartLocation;
};
