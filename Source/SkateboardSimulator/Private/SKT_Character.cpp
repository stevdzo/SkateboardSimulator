// Fill out your copyright notice in the Description page of Project Settings.


#include "SKT_Character.h"

#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASKT_Character::ASKT_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurnRate = 0.0f;
	
	// bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
	// // GetCharacterMovement()->JumpZVelocity = 700.f;
	// // GetCharacterMovement()->AirControl = 0.35f;
	// // GetCharacterMovement()->MaxWalkSpeed = 900.f;
	// // GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	// // GetCharacterMovement()->BrakingDecelerationWalking = 200.f;
	// // GetCharacterMovement()->MaxAcceleration = 500.f;
	// // GetCharacterMovement()->BrakingFrictionFactor = 0.1f;
	// // GetCharacterMovement()->bUseSeparateBrakingFriction = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	SkateboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkateboardMeshComponent"));
	SkateboardMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASKT_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASKT_Character::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	DoMove(MovementVector.X, MovementVector.Y);
}

void ASKT_Character::MoveComplete(const FInputActionValue& Value)
{
	//MovementVector = FVector2D::ZeroVector;
}

void ASKT_Character::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ASKT_Character::DoMove(float Right, float Forward)
{
	AddMovementInput(GetActorForwardVector(), Forward);

	// const FRotator Rotation = Controller->GetControlRotation();
	// const FRotator YawRotation(0, Rotation.Yaw, 0);
	// const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// AddMovementInput(RightDirection, Right);
	
	TurnRate = Right;
}

void ASKT_Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ASKT_Character::DoJumpStart()
{
	Jump();
}

void ASKT_Character::DoJumpEnd()
{
	StopJumping();
}

// Called every frame
void ASKT_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}
	
	constexpr float BaseRotationSpeedDegreesPerSecond = 180.f;
	constexpr float MinSpeedThreshold = 10.f;
	
	const float CurrentSpeed = GetVelocity().Size();
	if (CurrentSpeed < MinSpeedThreshold)
	{
		return;
	}
	
	const float SpeedFactor = CurrentSpeed / FMath::Max(1.0f, GetCharacterMovement()->MaxWalkSpeed);
	const float ActualRotationSpeed = BaseRotationSpeedDegreesPerSecond * SpeedFactor;
	
	const float YawDelta = TurnRate * ActualRotationSpeed * DeltaTime;
	
	FRotator DeltaRotation(0.f, YawDelta, 0.f);
	
	AddActorWorldRotation(DeltaRotation);
}

// Called to bind functionality to input
void ASKT_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ASKT_Character::Move);
		
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &ASKT_Character::Look);
		
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Started, this, &ASKT_Character::Jump);
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Completed, this, &ASKT_Character::StopJumping);
	}
}
