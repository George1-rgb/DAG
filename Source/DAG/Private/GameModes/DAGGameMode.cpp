// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DAGGameMode.h"
#include "GameModes/DAGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameActors/DAGDice.h"
#include "GameActors/DAGDeskPlate.h"
#include "GameActors/DAGBasePawn.h"
#include "Net/UnrealNetwork.h"
#include "GameModes/DAGGameStateBase.h"
#include "Player/DAGPlayerController.h"
#include "Player/DAGPawn.h"

ADAGGameMode::ADAGGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	GameStateClass = ADAGGameStateBase::StaticClass();
	PlayerControllerClass = ADAGPlayerController::StaticClass();
}

void ADAGGameMode::RollDices()
{
	if (HasAuthority())
	{
		ServerRollDices(); // если сервер Ч сразу кидаем
	}
	else
	{
		ServerRollDices(); // клиент просит сервер кинуть
	}
}

void ADAGGameMode::ServerRollDices_Implementation()
{
	if (!GetWorld())
		return;
	const auto instGameInstance = GetWorld()->GetGameInstance<UDAGGameInstance>();
	if (!instGameInstance)
		return;

	TArray<AActor*> arrDices;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), diceClass, arrDices);
	for (auto pOldDice : arrDices)
		pOldDice->Destroy();

	int nDicesCnt = instGameInstance->GetDicesCount();
	FVector SpawnLocation = instGameInstance->GetDicesLocationDef();
	for (int i = 0; i < nDicesCnt; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnLocation.X += 10.0;
		double fRandX = FMath::RandRange(-180.0, 180.0);
		double fRandY = FMath::RandRange(-180.0, 180.0);
		double fRandZ = FMath::RandRange(-180.0, 180.0);
		FRotator rotator(fRandX, fRandY, fRandZ);
		auto SpawnedDice = GetWorld()->SpawnActor<ADAGDice>(diceClass, SpawnLocation, rotator, SpawnInfo);
		if (!SpawnedDice)
			continue;
	}

	auto ApplyImpulse = [&]()
		{
			const auto instGameInstance = GetWorld()->GetGameInstance<UDAGGameInstance>();
			if (!instGameInstance)
				return;
			TArray<AActor*> arrDices;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), diceClass, arrDices);

			for (auto dice : arrDices)
			{
				UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(dice->GetRootComponent());
				double fRandXComponent = FMath::RandRange(instGameInstance->GetMinImpulse(), instGameInstance->GetMaxImpulse());
				double fRandYComponent = FMath::RandRange(instGameInstance->GetMinImpulse(), instGameInstance->GetMaxImpulse());

				staticMesh->AddImpulse(FVector(fRandXComponent, fRandYComponent, instGameInstance->GetZImpulse()));
			}
			m_bDiceRolling = true;
		};

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, ApplyImpulse, 0.2, false);
}

void ADAGGameMode::SetDicesVals_Implementation(const TArray<int>& nDicesVals)
{
	if (!GetWorld())
		return;
	auto instGameState = Cast<ADAGGameStateBase>(GetWorld()->GetGameState());
	if (!instGameState)
		return;
	instGameState->SetDicesValues(nDicesVals);
}

ADAGDeskPlate* ADAGGameMode::GetDeskPlate(const EPlateType& plateType, const int& nPlayerNum, const int& nFieldNum) const
{
	auto pItem = *m_vPlates.FindByPredicate([&](const TObjectPtr<ADAGDeskPlate>& pPlate)
		{
			return plateType == pPlate->GetPlateInfo().m_ePlateType &&
				   nFieldNum == pPlate->GetPlateInfo().m_nFieldNum &&
				   nPlayerNum == pPlate->GetPlateInfo().m_nPlayerNumber;
		});
	return pItem;
}

void ADAGGameMode::HightLigthPlates()
{
	//TODO:: выделение только нужных объектов

	for (auto& pPlate : m_vPlates)
		pPlate->SetHightLight(true);
}

void ADAGGameMode::DeselectPlates()
{
	for (auto& pPlate : m_vPlates)
		pPlate->SetHightLight(false);
}

void ADAGGameMode::MovePawn(const FDAGPlateInfo& fPlateInfo)
{
	if (!m_pCurrentSelPawn)
		return;

	//m_pCurrentSelPawn->SetActorLocation(FVector(fPlateInfo.m_fX, fPlateInfo.m_fY, fPlateInfo.m_fZ), true);
	m_pCurrentSelPawn->SetNewActorLocation(FVector(fPlateInfo.m_fX, fPlateInfo.m_fY, fPlateInfo.m_fZ));
}

void ADAGGameMode::Tick(float DeltaSeconds)
{
	if (!m_bDiceRolling)
		return;
	if (!GetWorld())
		return;

	

	TArray<AActor*> arrDices;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), diceClass, arrDices);
	bool bTemp = false;
	for (const auto pActor : arrDices)
	{
		bTemp = true;
		const auto pDice = Cast<ADAGDice>(pActor);
		bool bDiceStopping = false;
		bDiceStopping = pDice->IsDiceStopping();
		if (!bDiceStopping)
		{
			bTemp = false;
			return;
		}
	}
	m_bCanShowDiceValues = bTemp;
	if (m_bCanShowDiceValues)
	{
		TArray<int> nDicesVals;
		for (const auto pActor : arrDices)
		{
			const auto pDice = Cast<ADAGDice>(pActor);
			nDicesVals.Add(pDice->GetValue());
		}
		SetDicesVals(nDicesVals);
		m_bCanShowDiceValues = false;
		m_bDiceRolling = false;
	}
}

void ADAGGameMode::StartPlay()
{
	Super::StartPlay();
	if (!GetWorld())
		return;

	TArray<AActor*> arrPlates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), plateClass, arrPlates);
	for (auto pActor : arrPlates)
	{
		auto pPlate = Cast<ADAGDeskPlate>(pActor);
		if (pPlate)
		{
			auto infoPlate = pPlate->GetPlateInfo();
			infoPlate.m_fX = pPlate->GetActorLocation().X;
			infoPlate.m_fY = pPlate->GetActorLocation().Y;
			infoPlate.m_fZ = pPlate->GetActorLocation().Z;
			pPlate->SetPlateInfo(infoPlate);
			m_vPlates.Add(pPlate);
		}
	}
}

void ADAGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("[GameMode] PostLogin for: %s | Role: %s"),
		*NewPlayer->GetName(),
		*UEnum::GetValueAsString(NewPlayer->GetLocalRole()));

	if (HasAuthority() && NewPlayer)
	{
		// —павним фиктивный Pawn, если не используем геймплейные Pawn'ы
		APawn* DummyPawn = GetWorld()->SpawnActor<APawn>(ADAGPawn::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		if (DummyPawn)
		{
			NewPlayer->Possess(DummyPawn);
		}
	}
}
