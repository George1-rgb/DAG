// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DAGDesk.generated.h"

class ADAGDeskPlate;
UCLASS()
class DAG_API ADAGDesk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADAGDesk();

	UFUNCTION(BlueprintCallable)
	void BuildDesk(const FVector vLocation, const int nX, const int nY);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D m_vDeskSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> m_vPlates;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<ADAGDeskPlate> m_cPlateClass;
};
