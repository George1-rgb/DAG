// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DAGGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DAG_API ADAGGameStateBase : public AGameState
{
	GENERATED_BODY()
public:
	ADAGGameStateBase();


	UPROPERTY(ReplicatedUsing=OnRepDicesValues)
	TArray<int> m_nDicesCurValues = {};

	void SetDicesValues(const TArray<int>& nDicesCurValues);
	UFUNCTION()
	void OnRepDicesValues();
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
