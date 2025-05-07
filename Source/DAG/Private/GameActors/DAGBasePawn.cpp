// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActors/DAGBasePawn.h"
#include "GameActors/DAGBasePawnController.h"
#include "Engine/Engine.h"
#include "Components/SceneComponent.h"

// Sets default values
ADAGBasePawn::ADAGBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	smRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(smRoot);

	smPawn = CreateDefaultSubobject<UStaticMeshComponent>("DiceStaticMesh");
	smPawn->SetupAttachment(smRoot);
	
	smPawn->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	smPawn->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	smPawn->SetGenerateOverlapEvents(true);

	smHighlight = CreateDefaultSubobject<UStaticMeshComponent>("Highlight");
	smHighlight->SetupAttachment(smPawn);
	smHighlight->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ADAGBasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADAGBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADAGBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADAGBasePawn::OnPawnClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Pawn was clicked!"));
	}
	smHighlight->SetHiddenInGame(false);
}

void ADAGBasePawn::Deselect()
{
	smHighlight->SetHiddenInGame(true);
}

