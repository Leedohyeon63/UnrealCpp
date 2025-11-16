

// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ResourceComponent.h"
#include "Player/WeaponActor.h"
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

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; //이동 방향을 바라보게 회전
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);

	Resource = CreateDefaultSubobject<UResourceComponent>(TEXT("Resource"));
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GetMesh())
	{
		AnimInstance = GetMesh()->GetAnimInstance();	// ABP 객체 가져오기
	}
	if (Resource)
	{
		Resource->OnStaminaEmpty.AddDynamic(this, &AActionCharacter::SetWalkMode);
	}

	IsSprint = false;
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

void AActionCharacter::OnAttackEnable(bool bEnable)
{
	if (CurrentWeapon.IsValid())
	{
		CurrentWeapon->AttackEnable(bEnable);
	}
	
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
	if (AnimInstance.IsValid() && Resource->HasEnoughStamina(AttackCost))
	{
		if (!AnimInstance->IsAnyMontagePlaying())
		{
			Resource->AddStamina(-AttackCost);	// 스태미너 감소
			PlayAnimMontage(AttackMontage);
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
		Resource->AddStamina(-3.0f * DeltaTime);	// 스태미너 감소
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


