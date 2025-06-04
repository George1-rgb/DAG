// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DAGPlayerController.h"
#include "GameActors/DAGBasePawn.h"
#include "GameModes/DAGGameMode.h"
#include "GameActors/DAGDeskPlate.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DAGBaseWidget.h"

ADAGPlayerController::ADAGPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true; 
}

void ADAGPlayerController::BeginPlay()
{
	Super::BeginPlay();

    FString RoleStr = HasAuthority() ? TEXT("Server") : TEXT("Client");
    FString LocalStr = IsLocalController() ? TEXT("LocalController") : TEXT("RemoteController");

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay: %s | %s"), *RoleStr, *LocalStr);

	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

    if (IsLocalController())
    {
        GameWidgets.Push(CreateWidget<UDAGBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
        for (auto GameWidget : GameWidgets)
        {
            if (!GameWidget) continue;
            GameWidget->AddToPlayerScreen();
            GameWidget->SetVisibility(ESlateVisibility::Visible);

            if (GameWidget->IsInViewport())
            {

               UE_LOG(LogTemp, Warning, TEXT("Yes"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("No"));
            }
        }
    }
}

void ADAGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ADAGPlayerController::OnLeftMouseClick);
}

void ADAGPlayerController::Tick(float DeltaSeconds)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, TEXT("Controller Tick"));
    }
}

void ADAGPlayerController::OnLeftMouseClick()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);
    auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
    if (!pGameMode)
        return;
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
