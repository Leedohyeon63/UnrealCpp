// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
void UActionAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* OwnerPawn = TryGetPawnOwner();
	if (OwnerPawn)
	{
		OwnerMovementComponent = OwnerPawn->GetMovementComponent();
	}
}

void UActionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerMovementComponent.IsValid())
	{
		//const UPawnMovementComponent* Movement = OwnerMovementComponent.Get();
		//Speed = Movement->Velocity.Size();
		Speed = OwnerMovementComponent.Get()->Velocity.Size();
	}

}