// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DAGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAG_API UDAGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	int GetDicesCount() const { return nDicesCount; }
	FVector GetDicesLocationDef() const { return vDicesLocationDef; }
	double GetMaxImpulse() const { return fMaxImpulse; }
	double GetMinImpulse() const { return fMinImpulse; }
	double GetZImpulse() const { return fZImpulse; }
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	int nDicesCount = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FVector vDicesLocationDef = FVector(0.0);
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	double fMaxImpulse = 100.0;
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	double fMinImpulse = -100.0;
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	double fZImpulse = 10.0;
};
