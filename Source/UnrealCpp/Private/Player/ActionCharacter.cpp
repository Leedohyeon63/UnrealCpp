// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ResourceComponent.h"
#include "Weapon/ConsumableWeapon.h"
#include "Weapon/WeaponActor.h"
#include "Item/IEquipable.h"
// Sets default values
AActionCharacter::AActionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));
	Springarm->SetupAttachment(RootComponent);
	Springarm->TargetArmLength = 350.0f;
	Springarm->SocketOffset = FVector(0,0,250);
	Springarm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(Springarm);
	PlayerCamera->SetRelativeRotation(FRotator(-20.0f,0.0f,0.0f));

	DropLocation = CreateDefaultSubobject<USceneComponent>(TEXT("DropLocation"));
	DropLocation->SetupAttachment(RootComponent);
	DropLocation->SetRelativeLocation(FVector(80.0f, 30.0f, 0.0f));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; //이동 방향을 바라보게 회전
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);

	Resource = CreateDefaultSubobject<UResourceComponent>(TEXT("Resource"));
	Status = CreateDefaultSubobject<UStatusComponent>(TEXT("PlayerStatus"));

	WeaponManager = CreateDefaultSubobject<UWeaponManager>(TEXT("WeaponManager"));


}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	if (Resource)
	{
		Resource->OnStaminaEmpty.AddDynamic(this, &AActionCharacter::SetWalkMode);
		if (Status)
		{
			Resource->SetMaxHealth(Status->GetMaxHP());
			Resource->SetMaxStamina(Status->GetMaxStamina());

			Resource->AddHP(Status->GetMaxHP());
			Resource->AddStamina(Status->GetMaxStamina());
		}
	}
	Super::BeginPlay();
	if (GetMesh())
	{
		AnimInstance = GetMesh()->GetAnimInstance();	// ABP 객체 가져오기

	}
	IsSprint = false;

	OnActorBeginOverlap.AddDynamic(this, &AActionCharacter::OnBeginOverlap);
}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	SpendRunstamina(DeltaTime);
	//if (IsSprint && !GetVelocity().IsNearlyZero() && !AnimInstance->IsAnyMontagePlaying())	// 달리기 모드인 상태에서 움직이면 스태미너를 소비한다.
	//{
	//	Resource->AddStamina(-3.0f * DeltaTime);	// 스태미너 감소
	//}
}

// Called to bind functionality to input
void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhanced)	// 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		enhanced->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AActionCharacter::OnMoveInput);
		enhanced->BindAction(IA_Roll, ETriggerEvent::Triggered, this, &AActionCharacter::OnRollInput);
		enhanced->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AActionCharacter::OnJumpInput
		
		);
		enhanced->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AActionCharacter::OnAttackInput);
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Started, 
			[this](const FInputActionValue& _) {
				SetSprintMode();
			});
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Completed,
			[this](const FInputActionValue& _) {
				SetWalkMode();
			});
	}
}

void AActionCharacter::AddItem_Implementation(EItemCode Code, int32 Count)
{
	const UEnum* EnumPtr = StaticEnum<EItemCode>();
	UE_LOG(LogTemp, Log, TEXT("아이템 추가 : %s"), *EnumPtr->GetDisplayNameTextByValue(static_cast<int8>(Code)).ToString());

	EquipWeapon(Code);
	CurrentWeapon->OnWeaponPickuped(Count);
}


void AActionCharacter::OnAttackEnable(bool bEnable)
{
	if (CurrentWeapon.IsValid())
	{
		CurrentWeapon->AttackEnable(bEnable);
	}
	
}

void AActionCharacter::EquipWeapon(EItemCode WeaponCode)
{

	if (CurrentWeapon.IsValid())
	{
		// 장비하고 있던 무기가 기본 무기가 아니면
		if (CurrentWeapon->GetItemCode() != EItemCode::BasicWeapon	// 장비하고 있던 무기가 Consumable이고
			&& CurrentWeapon->GetItemCode() != WeaponCode			// 새로 장비할 무기와 다른 종류고
			&& CurrentWeapon->CanAttack())							// 장비하고 있던 무기에 회수가 남아있는 상황이면
		{
			DropCurrentWeapon(CurrentWeapon->GetItemCode());
		}

		// 장비하고 있던 무기는 해제
		CurrentWeapon->WeaponActivate(false);
	}

	// WeaponCode에 해당하는 무기 장비
	CurrentWeapon = WeaponManager->GetEquippedWeapon(WeaponCode);
	CurrentWeapon->WeaponActivate(true);
}

void AActionCharacter::OnCurrentWeaponThrowaway()
{
	DropCurrentWeapon(CurrentWeapon->GetItemCode());
}

void AActionCharacter::OnMoveInput(const FInputActionValue& Invalue)
{
	FVector2D InputDir = Invalue.Get<FVector2D>();
	//UE_LOG(LogTemp, Log, TEXT("Dir : %.1f, %.1f"), InputDir.X, InputDir.Y);
	FVector MoveDir(InputDir.Y, InputDir.X, 0.0f);

	FQuat ContorolYawRotation = FQuat(FRotator(0, GetControlRotation().Yaw, 0));
	MoveDir = ContorolYawRotation.RotateVector(MoveDir);

	AddMovementInput(MoveDir);
}

void AActionCharacter::OnRollInput(const FInputActionValue& Invalue)
{
	if (AnimInstance.IsValid())
	{
		if (!AnimInstance->IsAnyMontagePlaying() && Resource->HasEnoughStamina(RollCost))
		{
			//if (!GetLastMovementInputVector().IsNearlyZero())
			//{
			//	SetActorRotation(GetLastMovementInputVector().Rotation());
			//}
			Resource->AddStamina(-RollCost);	// 스태미너 감소
			PlayAnimMontage(RollMontage);
		}
	}
}

void AActionCharacter::OnAttackInput(const FInputActionValue& Invalue)
{
	
	if (AnimInstance.IsValid() && Resource->HasEnoughStamina(AttackCost)&& (CurrentWeapon.IsValid() && CurrentWeapon->CanAttack()))
	{
		if (!AnimInstance->IsAnyMontagePlaying())
		{
			Resource->AddStamina(-AttackCost);	// 스태미너 감소
			PlayAnimMontage(AttackMontage);
			FOnMontageEnded OnMontageEnded;
			OnMontageEnded.BindUObject(this, &AActionCharacter::OnAttackMontageEnded);
			AnimInstance->Montage_SetEndDelegate(OnMontageEnded);

			if (CurrentWeapon.IsValid())
			{
				CurrentWeapon->OnAttack();
			}
		}
		else if (AnimInstance->GetCurrentActiveMontage() == AttackMontage)
		{
			SectionJumpForCombo();

		}
	}

	
}

void AActionCharacter::OnJumpInput(const FInputActionValue& Invalue)
{
	Jump();
}

void AActionCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (CurrentWeapon.IsValid() && !CurrentWeapon->CanAttack())	// CurrentWeapon이 공격할 수 없으면(=사용회수가 안남았다)
	{
		//DropUsedWeapon();		
		DropWeapon(CurrentWeapon->GetItemCode());	// 현재 사용 중인 무기 버리기
		EquipWeapon(EItemCode::BasicWeapon);
	}
}

void AActionCharacter::OnWeaponThrowaway()
{
	if (CurrentWeapon.IsValid() && !CurrentWeapon->CanAttack())	// CurrentWeapon이 공격할 수 없으면(=사용회수가 안남았다)
	{
		UE_LOG(LogTemp, Log, TEXT("다쓴 무기 버리기"));
		TSubclassOf<AActor>* usedClass = UsedWeapon.Find(CurrentWeapon->GetItemCode());
		if (usedClass)
		{
			GetWorld()->SpawnActor<AActor>(
				*usedClass,
				DropLocation->GetComponentLocation(),
				GetActorRotation()
			);
		}
		
		// FRotator()를 캐릭터의 forward 방향을 바라보는 회전으로 대체하기
	}
}
//void AActionCharacter::DropWeapon(EItemCode WeaponCode)
//{
//	UE_LOG(LogTemp, Log, TEXT("다쓴 무기 버리기"));
//	if (TSubclassOf<AUsedWeapon> usedClass = WeaponManager->GetUsedWeaponClass(WeaponCode))
//	{
//		GetWorld()->SpawnActor<AActor>(
//			usedClass,
//			DropLocation->GetComponentLocation(),
//			GetActorRotation());
//	}
//}

void AActionCharacter::DropWeapon(EItemCode WeaponCode)
{
	UE_LOG(LogTemp, Log, TEXT("다쓴 무기 버리기"));
	if (TSubclassOf<AUsedWeapon> usedClass = WeaponManager->GetUsedWeaponClass(WeaponCode))
	{
		GetWorld()->SpawnActor<AActor>(
			usedClass,
			DropLocation->GetComponentLocation(),
			GetActorRotation());
	}
}

void AActionCharacter::DropCurrentWeapon(EItemCode WeaponCode)
{
	if (CurrentWeapon.IsValid() && (CurrentWeapon->GetItemCode() != EItemCode::BasicWeapon))
	{
		if (TSubclassOf<APickUp> pickupClass = WeaponManager->GetPickupWeaponClass(WeaponCode))
		{
			APickUp* pickup = GetWorld()->SpawnActor<APickUp>(
				pickupClass,
				DropLocation->GetComponentLocation(),
				GetActorRotation()
			);

			// 새로 생긴 픽업에 남은 회수 넣기
			AConsumableWeapon* conWeapon = Cast<AConsumableWeapon>(CurrentWeapon);
			pickup->SetPickupCount(conWeapon->GetRemainingUseCount());

			FVector velocity = (GetActorForwardVector() + GetActorUpVector()) * 300.0f;
			pickup->AddImpulse(velocity);
		}
	}
}


void AActionCharacter::SectionJumpForCombo()
{
	if (SectionJumpNotify.IsValid() && bComboReady)
	{
		UAnimMontage* Current = AnimInstance->GetCurrentActiveMontage();
		AnimInstance->Montage_SetNextSection(
			AnimInstance->Montage_GetCurrentSection(Current),
			SectionJumpNotify->GetNextSectionName(),
			Current
		);
		Resource->AddStamina(-AttackCost);
		if (CurrentWeapon.IsValid())
		{
			CurrentWeapon->OnAttack();
		}
		bComboReady = false;	
	}
}

void AActionCharacter::SpendRunstamina(float DeltaTime)
{
	if (IsSprint &&
		!GetVelocity().IsNearlyZero() && 
		AnimInstance.IsValid() &&
		!AnimInstance->IsAnyMontagePlaying())	// 달리기 모드인 상태에서 움직이면 스태미너를 소비한다.
	{
		Resource->AddStamina(-9.0f * DeltaTime);	// 스태미너 감소
	}
}


void AActionCharacter::SetSprintMode()
{
	//UE_LOG(LogTemp, Log, TEXT("달리기"))
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	IsSprint = true;
}

void AActionCharacter::SetWalkMode()
{
	//UE_LOG(LogTemp, Log, TEXT("걷기"))
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	IsSprint = false;
}

void AActionCharacter::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Log, TEXT("Char overlap : other is %s"), *OtherActor->GetName());

	// Implements를 이용한 인터페이스 사용
	if (OtherActor && OtherActor->Implements<UIEquipable>())	// OtherActor가 IPickable인터페이스를 구현했는지 확인
	{
		IIEquipable::Execute_OnPickUp(OtherActor, this);	// 구현이 되어 있으면 실행
	}
}

//void AActionCharacter::OnWeaponUseEnded()
//{
//	UE_LOG(LogTemp, Log, TEXT("무기 사용 끝"));
//
//}


