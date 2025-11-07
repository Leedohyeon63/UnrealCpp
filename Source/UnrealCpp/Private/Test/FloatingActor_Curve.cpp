// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/FloatingActor_Curve.h"

void AFloatingActor_Curve::OnFloatingMeshUpdate(float DeltaTime)
{
	if (HeightCurve)
	{
		rad += DeltaTime;
		float CurveInput = FMath::Fmod(rad/Duration, 1.0f);
		float CurveValue = HeightCurve->GetFloatValue(CurveInput);
		BodyMesh->SetRelativeLocation(FVector(0, 0, CurveValue * MoveHeight));
		BodyMesh->AddRelativeRotation(FRotator(0, SpinSpeed * DeltaTime, 0));
		UE_LOG(LogTemp, Log, TEXT("%f"), CurveValue);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("X"));

		Super::OnFloatingMeshUpdate(DeltaTime);
	}
}
