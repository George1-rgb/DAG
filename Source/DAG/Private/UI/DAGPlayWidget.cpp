// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DAGPlayWidget.h"
#include "Components/Button.h"
#include "GameModes/DAGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DAGGameMode.h"

void UDAGPlayWidget::NativeOnInitialized()
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

	auto instGameInstance = GetWorld()->GetGameInstance<UDAGGameInstance>();
	if (!instGameInstance)
		return FString();

	FString strTmp;
	for (const auto nVal : instGameInstance->GetDicesValues())
	{
		strTmp.Append(" ");
		strTmp.Append(FString::FromInt(nVal));
	}
	return strTmp;
}

void UDAGPlayWidget::OnRollDices()
{
	if (!GetWorld())
		return;

	auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
	if (!pGameMode)
		return;
	pGameMode->RollDices();
}
