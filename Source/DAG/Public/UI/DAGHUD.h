// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DAGHUD.generated.h"

/**
 * 
 */
class UDAGBaseWidget;
UCLASS()
class DAG_API ADAGHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
protected:
	virtual void BeginPlay() override;
};
