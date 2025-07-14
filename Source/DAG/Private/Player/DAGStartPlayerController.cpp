// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DAGStartPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DAGBaseWidget.h"
#include "UI/DAGMainMenuWidget.h"
#include "GameModes/StartGameMode.h"

ADAGStartPlayerController::ADAGStartPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bShowMouseCursor = true;
}

void ADAGStartPlayerController::BeginPlay()
{
    // Выполним подключение с небольшой задержкой
   // GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ADAGStartPlayerController::ConnectToServer);
	Super::BeginPlay();
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
    if (IsLocalController())
    {
        GameWidgets.Push(CreateWidget<UDAGBaseWidget>(GetWorld(), MainMenuWidgetClass));
        for (auto GameWidget : GameWidgets)
        {
            if (!GameWidget) continue;
            GameWidget->AddToViewport();
            auto pMainMenuWgt = Cast<UDAGMainMenuWidget>(GameWidget);
            if (pMainMenuWgt)
                GameWidget->SetVisibility(ESlateVisibility::Visible);
            else
                GameWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void ADAGStartPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ADAGStartPlayerController::ConnectToServer(const FString& strIP)
{
	// Проверим: сервер это или клиент
	if (!IsRunningDedicatedServer())
	{
		// Это клиент выполняем автоподключение
		FString ServerAddress = strIP;  // Укажи свой адрес и порт
		UE_LOG(LogTemp, Log, TEXT("Trying to connect to server at %s"), *ServerAddress);

		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->ClientTravel(ServerAddress, ETravelType::TRAVEL_Absolute);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("World is null, cannot connect to server"));
		}
	}
	else
	{
		// Это сервер никаких подключений
		UE_LOG(LogTemp, Log, TEXT("Running as dedicated server, no client connection needed"));
	}
}
