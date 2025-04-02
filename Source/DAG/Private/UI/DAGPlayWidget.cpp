// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DAGPlayWidget.h"
#include "Components/Button.h"
#include "GameModes/DAGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameActors/DAGDice.h"

void UDAGPlayWidget::NativeOnInitialized()
{
	if (btnRollDices)
	{
		btnRollDices->OnClicked.AddDynamic(this, &UDAGPlayWidget::OnRollDices);
	}
}

void UDAGPlayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

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
	bCanShowDiceValues = bTemp;
	if (bCanShowDiceValues)
	{
		for (const auto pActor : arrDices)
		{
			const auto pDice = Cast<ADAGDice>(pActor);
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, FString::SanitizeFloat(pDice->GetValue()));
		}
		bCanShowDiceValues = false;
		m_bDiceRolling = false;
	}
}

void UDAGPlayWidget::OnRollDices()
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
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, ApplyImpulse, 0.5, false);
	
}
