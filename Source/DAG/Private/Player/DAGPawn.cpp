// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DAGPawn.h"

// Sets default values
ADAGPawn::ADAGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADAGPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADAGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADAGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

