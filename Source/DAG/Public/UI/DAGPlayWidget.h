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
UCLASS()
class DAG_API UDAGPlayWidget : public UDAGBaseWidget
{
	GENERATED_BODY()
//public:
//	FOnDiceRoll m_OnDiceRoll;
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* btnRollDices;

	virtual void NativeOnInitialized() override;
public:
	// Called every frame
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetDicesValues() const;
private:
	UFUNCTION()
		void OnRollDices();
};
