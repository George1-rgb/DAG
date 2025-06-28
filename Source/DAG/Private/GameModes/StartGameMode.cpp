// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/StartGameMode.h"
#include "Player/DAGStartPlayerController.h"



AStartGameMode::AStartGameMode()
{
	PlayerControllerClass = ADAGStartPlayerController::StaticClass();
}

void AStartGameMode::StartPlay()
{
	Super::StartPlay();
}

void AStartGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
