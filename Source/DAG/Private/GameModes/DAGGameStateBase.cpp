// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DAGGameStateBase.h"
#include "Net/UnrealNetwork.h"

ADAGGameStateBase::ADAGGameStateBase()
{
	bReplicates = true;
}

void ADAGGameStateBase::SetDicesValues(const TArray<int>& nDicesCurValues)
{
	if (HasAuthority())  // ѕровер€ем, что это сервер
	{
		m_nDicesCurValues = nDicesCurValues;
	}
}

void ADAGGameStateBase::OnRepDicesValues()
{
	// «десь код, который выполнитс€ при изменении Score на клиенте
	//UE_LOG(LogTemp, Log, TEXT("DicesValues обновилс€ на клиенте"));
}

void ADAGGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// –еплицируем переменную Score
	DOREPLIFETIME(ADAGGameStateBase, m_nDicesCurValues);
}
