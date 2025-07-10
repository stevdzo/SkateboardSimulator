// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SKT_PlayerController.generated.h"

class UInputMappingContext;
class ASKT_Character;

/**
 * 
 */
UCLASS()
class SKATEBOARDSIMULATOR_API ASKT_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

protected:

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	
	// A reference to the player character
	UPROPERTY()
	ASKT_Character* PlayerCharacter = nullptr;
};
