// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DAG_API AStartGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AStartGameMode();
protected:
	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
};
