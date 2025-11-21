// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/MyAnimNotifyState.h"
#include "Player/ActionCharacter.h"

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}

	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->OnAreaColisionEnable(true);
	}
	UE_LOG(LogTemp, Log, TEXT("Notify address : %p"), this);
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->OnAreaColisionEnable(false);

	}
}
