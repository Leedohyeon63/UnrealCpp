// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class UNREALCPP_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnFloatingMeshUpdate(float DeltaTime); // 스태틱메시 움직임 업데이트 함수

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BodyMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float speed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveHeight = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpinSpeed = 50.0f;

	float rad = 0.0f;
	FVector CurrrentHeight;
};
