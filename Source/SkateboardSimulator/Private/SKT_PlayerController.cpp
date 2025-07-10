// Fill out your copyright notice in the Description page of Project Settings.

#include "SKT_PlayerController.h"
#include <EnhancedInputSubsystems.h>

 void ASKT_PlayerController::OnPossess(APawn* aPawn)
 {
 	Super::OnPossess(aPawn);

 	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
 	{
 		Subsystem->AddMappingContext(InputMappingContext, 0);
 	}
 }

 void ASKT_PlayerController::OnUnPossess()
 {
 	Super::OnUnPossess();
 }


