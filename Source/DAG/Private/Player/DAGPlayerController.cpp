// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DAGPlayerController.h"
#include "GameActors/DAGBasePawn.h"
#include "GameModes/DAGGameMode.h"
#include "GameActors/DAGDeskPlate.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DAGBaseWidget.h"
#include "GameModes/DAGGameStateBase.h"

ADAGPlayerController::ADAGPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true; 
}

void ADAGPlayerController::ServerRollDices_Implementation()
{
    if (!GetWorld())
        return;

    auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
    if (!pGameMode)
        return;
    pGameMode->RollDices();
}

void ADAGPlayerController::ServerSetSelPawn_Implementation(ADAGBasePawn* selPawn)
{
	if (!GetWorld())
		return;

	auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
	if (!pGameMode)
		return;
	pGameMode->SetSelPawn(selPawn);
}

void ADAGPlayerController::ServerDeselectPlates_Implementation()
{
	auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
	if (!pGameMode)
		return;
	pGameMode->DeselectPlates();
}

void ADAGPlayerController::ServerHightlightPlates_Implementation()
{
	auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
	if (!pGameMode)
		return;
	pGameMode->HightLigthPlates();
}

void ADAGPlayerController::ServerDeselectCurSelPawn_Implementation()
{
	auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
	if (!pGameMode)
		return;
	pGameMode->DeselectCurSelPawn();
}

void ADAGPlayerController::ServerMoveSelPawn_Implementation(const FDAGPlateInfo& fPlateInfo)
{
	auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
	if (!pGameMode)
		return;
	pGameMode->MovePawn(fPlateInfo);
}

void ADAGPlayerController::ServerOnSelPawnClicked_Implementation()
{
	auto pGameMode = Cast<ADAGGameMode>(GetWorld()->GetAuthGameMode());
	if (!pGameMode)
		return;
	pGameMode->OnCurSelPawnClicked();
}

void ADAGPlayerController::ServerApplyPointDamage_Implementation(ADAGBasePawn* damagedPawn, ADAGBasePawn* damageCauser, const FHitResult& Hit)
{
	UGameplayStatics::ApplyPointDamage(damagedPawn, 100.0, FVector(), Hit, damageCauser->GetController(), damageCauser, damageCauser->GetDamageType());
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
            GameWidget->AddToViewport();
            GameWidget->SetVisibility(ESlateVisibility::Visible);
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
	if (!IsLocalController())
		return;
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	auto pGameState = Cast<ADAGGameStateBase>(GetWorld()->GetGameState());
	if (!pGameState)
		return;
	auto pCurSelPawn = pGameState->m_pCurrentSelPawn;
	if (Hit.bBlockingHit)
	{
		ADAGBasePawn* ClickedPawn = Cast<ADAGBasePawn>(Hit.GetActor());
		if (ClickedPawn)
		{
			if (pCurSelPawn)
			{
				ServerDeselectCurSelPawn();
				if (ClickedPawn->GetCommandNum() != pCurSelPawn->GetCommandNum())
				{
					ServerDeselectPlates();
					FVector vNewLoc = ClickedPawn->GetActorLocation();
					ServerMoveSelPawn(FDAGPlateInfo(vNewLoc.X, vNewLoc.Y, vNewLoc.Z));
					ServerApplyPointDamage(ClickedPawn, pCurSelPawn, Hit);
					ServerSetSelPawn(nullptr);
					return;
				}
			}
			ServerSetSelPawn(ClickedPawn);
			ServerOnSelPawnClicked();
			ServerHightlightPlates();

		}
		else if (pCurSelPawn)
		{
			ADAGDeskPlate* ClickedPlate = Cast<ADAGDeskPlate>(Hit.GetActor());
			if (ClickedPlate && ClickedPlate->IsSelected())
			{
				ServerMoveSelPawn(ClickedPlate->GetPlateInfo());
			}
			ServerDeselectCurSelPawn();
			ServerSetSelPawn(nullptr);
			ServerDeselectPlates();
		}
	}
}
