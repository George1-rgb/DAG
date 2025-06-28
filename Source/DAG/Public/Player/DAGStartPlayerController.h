// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DAGStartPlayerController.generated.h"

/**
 * 
 */
class UDAGBaseWidget;
UCLASS()
class DAG_API ADAGStartPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADAGStartPlayerController();
	void ConnectToServer(const FString& strIP);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MainMenuWidgetClass;
	private:
	 UPROPERTY()
     TArray<UDAGBaseWidget*> GameWidgets;

};
