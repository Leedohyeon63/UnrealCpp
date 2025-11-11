// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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


}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Log, TEXT("%f"), Stamina)

	Super::Tick(DeltaTime);
	if (IsSprint && Stamina > 0)
	{
		Stamina -= DeltaTime * 3.0f;
		//UE_LOG(LogTemp, Log, TEXT("%f"), Stamina)
	}
	else
	{
		SetWalkMode();
	}

	if (!IsSprint && !AnimInstance->Montage_IsPlaying(RollMontage))
	{
		StaminaTime +=DeltaTime;
		if (StaminaTime > StaminaCoolDown)
		{
			Stamina += DeltaTime * StaminaInProve;
			if (Stamina >= 50.0f)
			{
				Stamina = MaxStamina;
			}
		}
		//UE_LOG(LogTemp, Log, TEXT("%f"), StaminaTime)
		//UE_LOG(LogTemp, Log, TEXT("%f"), Stamina)
	}
	else
	{
		StaminaTime = 0.0f;
	}
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
		if (!AnimInstance->IsAnyMontagePlaying())
		{
			//if (!GetLastMovementInputVector().IsNearlyZero())
			//{
			//	SetActorRotation(GetLastMovementInputVector().Rotation());
			//}
			if (Stamina >= RollCost)
			{
				PlayAnimMontage(RollMontage);
				Stamina -= RollCost;
				//UE_LOG(LogTemp, Log, TEXT("%f"), Stamina)
			}

		}
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

