// Fill out your copyright notice in the Description page of Project Settings.


#include "SKT_HudWidget.h"
#include "Components/TextBlock.h"

void USKT_HudWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USKT_HudWidget::UpdateXP(int32 NewXP)
{
	if (XPText)
	{
		XPText->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewXP)));
	}
}

