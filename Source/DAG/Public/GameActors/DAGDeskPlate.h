// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/DAGTypes.h"
#include "DAGDeskPlate.generated.h"

UCLASS()
class DAG_API ADAGDeskPlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADAGDeskPlate();
	void SetPlateInfo(const FDAGPlateInfo& info);
	const FDAGPlateInfo& GetPlateInfo() const { return m_FPlateInfo; }
	void SetHightLight(bool bHightLight);
	bool IsSelected() const { return m_bIsSelected; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> m_pPlateMesh;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> m_pHightLight;
#endif
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FDAGPlateInfo m_FPlateInfo;
	bool m_bIsSelected = false;
};
