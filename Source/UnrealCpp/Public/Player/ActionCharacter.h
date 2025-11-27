// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Notify/AnimNotifyState_SectionJump.h"
#include "InventoryOwner.h"
#include "Player/WeaponManager.h"
#include "HasHealth.h"
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

	virtual void AddItem_Implementation(EItemCode Code, int32 Count) override;
	virtual void AddWeapon_Implementation(EWeaponCode Code, int32 UseCount) override;
	virtual void AddConsume_Implementation(EItemCode Code) override;
	virtual void AddMoney_Implementation(int32 Income) override;
	virtual void RemoveMoney_Implementation(int32 Expense) override;

	virtual void HealHP_Implementation(float InHP);

	virtual void DamageHP_Implementation(float Damage);



	void OnAttackEnable(bool bEnable);

	void OnWeaponTrailEnable(bool bEnable);

	void OnAreaColisionEnable(bool bEnable);


	UResourceComponent* GetResourceComponent() { return Resource; }
	UStatusComponent* GetStatusComponent() { return Status; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(EWeaponCode WeaponCode);
	
	UFUNCTION(BlueprintCallable, Category = "pickup")
	void ItemConsume(EItemCode Code);

	inline void SetSectionJumpNotify(class UAnimNotifyState_SectionJump* InSectionjumpNotify) 
	{
		SectionJumpNotify = InSectionjumpNotify;
		bComboReady = InSectionjumpNotify != nullptr;

	}

	//UFUNCTION(BlueprintCallable)
	//void OnWeaponThrowaway(EItemCode WeaponCode);

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//void DropWeapon(EItemCode WeaponCode);

	UFUNCTION(BlueprintCallable)
	void OnCurrentWeaponThrowaway();

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

	//UFUNCTION(BlueprintCallable, Category = "Player")
	//void OnWeaponUseEnded();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<USpringArmComponent> Springarm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<UCameraComponent> PlayerCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<UCameraShakeBase> PlayerCameraShake = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	TObjectPtr<UResourceComponent> Resource = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Status")
	TObjectPtr<class UStatusComponent> Status = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapon")
	TObjectPtr<USceneComponent> DropLocation = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapon")
	TObjectPtr<class UWeaponManager> WeaponManager = nullptr;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Weapon")
	TMap<EItemCode, TSubclassOf<AActor>> UsedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Weapon")
	TMap<EItemCode, TSubclassOf<AActor>> ReusableWeapon;
private:
	UPROPERTY()
	TWeakObjectPtr<UAnimInstance> AnimInstance = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UAnimNotifyState_SectionJump> SectionJumpNotify = nullptr;

	bool bComboReady = false;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Weapon", meta = (AllowPrivateAccess = "true"))
	//bool bWeaponUseEnded = false;
private:
	void SectionJumpForCombo();
	void SpendRunstamina(float DeltaTime);
	void DropCurrentWeapon(EWeaponCode WeaponCode);
	void DropWeapon(EWeaponCode WeaponCode);
};
