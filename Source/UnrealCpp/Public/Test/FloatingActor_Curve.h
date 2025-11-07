// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Test/FloatingActor.h"
#include "FloatingActor_Curve.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API AFloatingActor_Curve : public AFloatingActor
{
	GENERATED_BODY()

protected:
	virtual void OnFloatingMeshUpdate(float DeltaTime) override;
	// 스태틱메시 움직임 업데이트 함수, 커브를 사용하고 커브가 없으면 부모 코드 사용

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCurveFloat> HeightCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 5.0f;


};
