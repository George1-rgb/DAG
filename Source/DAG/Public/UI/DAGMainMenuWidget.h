// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DAGBaseWidget.h"
#include "DAGMainMenuWidget.generated.h"

/**
 * 
 */
class UButton;
class UEditableTextBox;
UCLASS()
class DAG_API UDAGMainMenuWidget : public UDAGBaseWidget
{
	GENERATED_BODY()
	
public:
	UDAGMainMenuWidget() {}
protected:
	virtual void NativeConstruct() override;
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_ConnectToServ;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPTextBox;

	FString m_strServerIP = "";

private:
	UFUNCTION()
		void OnConnectServer();
};
