// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AnimNotifyState_WeaponTrail.h"
#include "Player/ActionCharacter.h"

void UAnimNotifyState_WeaponTrail::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}

	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->OnWeaponTrailEnable(true);
	}
	UE_LOG(LogTemp, Log, TEXT("Notify address : %p"), this);
}

void UAnimNotifyState_WeaponTrail::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->OnWeaponTrailEnable(false);

	}
}