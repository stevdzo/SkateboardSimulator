// Fill out your copyright notice in the Description page of Project Settings.


#include "SKT_AnimInstance.h"

#include "SKT_Character.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

void USKT_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (ASKT_Character* Player = Cast<ASKT_Character>(TryGetPawnOwner()))
	{
		PlayerReference = Player;
	}
}

void USKT_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerReference)
	{
		Speed = PlayerReference->GetVelocity().Size();
		bIsInAir = PlayerReference->GetMovementComponent()->IsFalling();
	}
	
	//OwningPawn->GetVelocity().Size();
}
