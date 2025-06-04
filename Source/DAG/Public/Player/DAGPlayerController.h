// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DAGPlayerController.generated.h"

/**
 * 
 */
class UDAGBaseWidget;
UCLASS()
class DAG_API ADAGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADAGPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	void OnLeftMouseClick();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

private:
	 UPROPERTY()
     TArray<UDAGBaseWidget*> GameWidgets;
};
