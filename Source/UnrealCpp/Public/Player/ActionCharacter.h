// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Notify/AnimNotifyState_SectionJump.h"
#include "InventoryOwner.h"
#include "ActionCharacter.generated.h"
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UResourceComponent;
class UStatusComponent;
UCLASS()
class UNREALCPP_API AActionCharacter : public ACharacter, public IInventoryOwner


{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddItem_Implementation(EItemCode Code);

	void OnAttackEnable(bool bEnable);

	UResourceComponent* GetResourceComponent() { return Resource; }
	UStatusComponent* GetStatusComponent() { return Status; }

	inline void SetSectionJumpNotify(class UAnimNotifyState_SectionJump* InSectionjumpNotify) 
	{
		SectionJumpNotify = InSectionjumpNotify;
		bComboReady = InSectionjumpNotify != nullptr;

	}

protected:
	void OnMoveInput(const FInputActionValue& Invalue);
	void OnRollInput(const FInputActionValue& Invalue);
	void OnAttackInput(const FInputActionValue& Invalue);
	void OnJumpInput(const FInputActionValue& Invalue);

	//void OnSprintInput(const FInputActionValue& Invalue);
	void SetSprintMode();

	UFUNCTION()
	void SetWalkMode();

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<USpringArmComponent> Springarm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<UCameraComponent> PlayerCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	TObjectPtr<UResourceComponent> Resource = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Status")
	TObjectPtr<class UStatusComponent> Status = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	TObjectPtr<UInputAction> IA_Move = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	TObjectPtr<UInputAction> IA_Sprint = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	TObjectPtr<UInputAction> IA_Roll = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	TObjectPtr<UInputAction> IA_Attack = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	TObjectPtr<UInputAction> IA_Jump = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float SprintSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float WalkSpeed = 600.0f;

	//스테미나 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float RollCost = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float AttackCost = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool IsSprint = false;
	//끝

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage")
	TObjectPtr<UAnimMontage> RollMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage")
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Weapon")
	TWeakObjectPtr<class AWeaponActor> CurrentWeapon = nullptr;



private:
	UPROPERTY()
	TWeakObjectPtr<UAnimInstance> AnimInstance = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UAnimNotifyState_SectionJump> SectionJumpNotify = nullptr;

	bool bComboReady = false;

private:
	void SectionJumpForCombo();
	void SpendRunstamina(float DeltaTime
	
	);
};
