// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SKT_PlayerController.generated.h"

class UInputMappingContext;
class ASKT_Character;
class USKT_HudWidget;

/**
 * 
 */
UCLASS()
class SKATEBOARDSIMULATOR_API ASKT_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<USKT_HudWidget> UserInterfaceClass;
	
	UPROPERTY()
	TObjectPtr<USKT_HudWidget> UserInterface = nullptr;
	
protected:

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

};
