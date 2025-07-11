// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SKT_HudWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SKATEBOARDSIMULATOR_API USKT_HudWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> XPText = nullptr;

public:

	UFUNCTION()
	void UpdateXP(int32 NewXP);
	
};
