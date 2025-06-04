// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DAGHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DAGGameMode.h"
#include "UI/DAGBaseWidget.h"

void ADAGHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ADAGHUD::BeginPlay()
{
	/*APlayerController* PC = GetOwningPlayerController();
	if (PC && PC->IsLocalController())
	{
		GameWidgets.Push(CreateWidget<UDAGBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
		for (auto GameWidget : GameWidgets)
		{
			if (!GameWidget) continue;
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}*/
}
