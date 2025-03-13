// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DAGBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAG_API UDAGBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* ShowAnimation;
public:
	void Show();
};
