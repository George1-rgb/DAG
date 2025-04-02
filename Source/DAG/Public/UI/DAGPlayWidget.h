// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DAGBaseWidget.h"
#include "Global/DAGTypes.h"
#include "DAGPlayWidget.generated.h"

/**
 * 
 */
class UButton;
class ADAGDice;
UCLASS()
class DAG_API UDAGPlayWidget : public UDAGBaseWidget
{
	GENERATED_BODY()
//public:
//	FOnDiceRoll m_OnDiceRoll;
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* btnRollDices;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		TSubclassOf<ADAGDice> diceClass;

	virtual void NativeOnInitialized() override;
public:
	// Called every frame
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
	UFUNCTION()
		void OnRollDices();

	bool bCanShowDiceValues;
	bool m_bDiceRolling = false;
};
