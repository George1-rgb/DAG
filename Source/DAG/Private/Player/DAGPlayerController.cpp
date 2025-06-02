// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DAGPlayerController.h"
#include "GameActors/DAGBasePawn.h"
#include "GameModes/DAGGameMode.h"
#include "GameActors/DAGDeskPlate.h"
#include "Kismet/GameplayStatics.h"

ADAGPlayerController::ADAGPlayerController()
{
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true; 
}

void ADAGPlayerController::BeginPlay()
{
	Super::BeginPlay();


	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}

void ADAGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ADAGPlayerController::OnLeftMouseClick);
}

void ADAGPlayerController::OnLeftMouseClick()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);
    auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
    auto pCurSelPawn = pGameMode->m_pCurrentSelPawn;
    if (Hit.bBlockingHit)
    {
        ADAGBasePawn* ClickedPawn = Cast<ADAGBasePawn>(Hit.GetActor());
        if (ClickedPawn)
        {
            if (pCurSelPawn)
            {
                pCurSelPawn->Deselect();
                if (ClickedPawn->GetCommandNum() != pCurSelPawn->GetCommandNum())
                {
                    pGameMode->DeselectPlates();
                    FVector vNewLoc = ClickedPawn->GetActorLocation();
                    pGameMode->MovePawn(FDAGPlateInfo(vNewLoc.X, vNewLoc.Y, vNewLoc.Z));
                    UGameplayStatics::ApplyPointDamage(ClickedPawn, 100.0, FVector(), Hit, pCurSelPawn->GetController(), this, pCurSelPawn->GetDamageType());
                    pGameMode->m_pCurrentSelPawn = nullptr;
                    return;
                }
            }
			pGameMode->m_pCurrentSelPawn = ClickedPawn;
			pGameMode->m_pCurrentSelPawn->OnPawnClicked();
			pGameMode->HightLigthPlates();
          
        }
        else if (pCurSelPawn)
        {
            ADAGDeskPlate* ClickedPlate = Cast<ADAGDeskPlate>(Hit.GetActor());
            if (ClickedPlate && ClickedPlate->IsSelected())
            {
                pGameMode->MovePawn(ClickedPlate->GetPlateInfo());
            }
            pCurSelPawn->Deselect();
            pGameMode->m_pCurrentSelPawn = nullptr;
            pGameMode->DeselectPlates();
        }
    }
}
