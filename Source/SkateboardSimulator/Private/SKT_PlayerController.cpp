// Fill out your copyright notice in the Description page of Project Settings.

#include "SKT_PlayerController.h"
#include <EnhancedInputSubsystems.h>

#include "SKT_Character.h"
#include "SKT_HudWidget.h"
#include "Blueprint/UserWidget.h"

void ASKT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!UserInterfaceClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASKT_PlayerController::BeginPlay -- UserInterfaceClass is not set."));
		return;
	}
	
	UserInterface = CreateWidget<USKT_HudWidget>(this, UserInterfaceClass);
	if (!UserInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASKT_PlayerController::BeginPlay -- UserInterface is nullptr."));
		return;
	}
	
	UserInterface->AddToViewport(9999);
	
	if (ASKT_Character* PlayerCharacter = Cast<ASKT_Character>(GetPawn()))
	{
		PlayerCharacter->OnXPChanged.AddDynamic(UserInterface.Get(), &USKT_HudWidget::UpdateXP);
	}
}

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


