// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DAGPlayWidget.h"
#include "Components/Button.h"
#include "GameModes/DAGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DAGGameMode.h"
#include "GameModes/DAGGameStateBase.h"
#include "Player/DAGPlayerController.h"

void UDAGPlayWidget::NativeConstruct()
{
	if (btnRollDices)
	{
		btnRollDices->OnClicked.AddDynamic(this, &UDAGPlayWidget::OnRollDices);
	}
}

void UDAGPlayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
}

FString UDAGPlayWidget::GetDicesValues() const
{
	if (!GetWorld())
		return FString();

	auto instGameState = Cast<ADAGGameStateBase>(GetWorld()->GetGameState());
	if (!instGameState)
		return FString();

	FString strTmp;
	for (const auto nVal : instGameState->m_nDicesCurValues)
	{
		strTmp.Append(" ");
		strTmp.Append(FString::FromInt(nVal));
	}
	return strTmp;
}

void UDAGPlayWidget::OnRollDices()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ADAGPlayerController* DAGPC = Cast<ADAGPlayerController>(PC))
		{
			DAGPC->ServerRollDices();
		}
	}
}
