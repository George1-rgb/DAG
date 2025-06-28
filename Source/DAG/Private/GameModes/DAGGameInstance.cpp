// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DAGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void UDAGGameInstance::Init()
{
    Super::Init();

    FString Address = TEXT("192.168.0.251:7777");  // или свой адрес сервера
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->ClientTravel(Address, TRAVEL_Absolute);
    }

    // Проверим: сервер это или клиент
    if (!IsRunningDedicatedServer())
    {
        // Это клиент → выполняем автоподключение
        FString ServerAddress = TEXT("");  // Укажи свой адрес и порт
        UE_LOG(LogTemp, Log, TEXT("Trying to connect to server at %s"), *ServerAddress);

        UWorld* World = GetWorld();
        if (World)
        {
            UGameplayStatics::OpenLevel(World, FName(*ServerAddress));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("World is null, cannot connect to server"));
        }
    }
    else
    {
        // Это сервер → никаких подключений
        UE_LOG(LogTemp, Log, TEXT("Running as dedicated server, no client connection needed"));
    }
}
