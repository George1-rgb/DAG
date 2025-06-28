// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DAGMainMenuWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Player/DAGStartPlayerController.h"


void UDAGMainMenuWidget::NativeConstruct()
{
	if (Btn_ConnectToServ)
	{
		Btn_ConnectToServ->OnClicked.AddDynamic(this, &UDAGMainMenuWidget::OnConnectServer);
	}
}

void UDAGMainMenuWidget::OnConnectServer()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ADAGStartPlayerController* DAGPC = Cast<ADAGStartPlayerController>(PC))
		{
			DAGPC->ConnectToServer(IPTextBox->GetText().ToString());
		}
	}
}
