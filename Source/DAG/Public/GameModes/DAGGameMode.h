// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Global/DAGTypes.h"
#include "DAGGameMode.generated.h"
/**
 * 
*/
class ADAGDice;
class ADAGDeskPlate;
class ADAGBasePawn;
UCLASS()
class DAG_API ADAGGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ADAGGameMode();

	void RollDices();
	void OnLeftMouseClick();

	UFUNCTION(Server, Reliable)
	void ServerRollDices();

	UFUNCTION(Client, Reliable)
	void SetDicesVals(const TArray<int>& nDicesVals);

	ADAGDeskPlate* GetDeskPlate(const EPlateType& plateType, const int& nPlayerNum, const int& nFieldNum) const;
	void HightLigthPlates();
	void DeselectPlates();
	void MovePawn(const FDAGPlateInfo& fPlateInfo);
	void DeselectCurSelPawn();
	void OnCurSelPawnClicked();
	void SetSelPawn(ADAGBasePawn* pSelPawn);
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TSubclassOf<ADAGDice> diceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TSubclassOf<ADAGDeskPlate> plateClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<FVector> PlayerStartLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<FRotator> PlayerStartRotations;
private:
	bool m_bCanShowDiceValues = false;
	bool m_bDiceRolling = false;
};
