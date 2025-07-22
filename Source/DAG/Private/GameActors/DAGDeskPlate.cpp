// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActors/DAGDeskPlate.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADAGDeskPlate::ADAGDeskPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	m_pPlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	SetRootComponent(m_pPlateMesh);
	//m_pPlateMesh->SetHiddenInGame(false);
	m_pPlateMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_pPlateMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
#if WITH_EDITORONLY_DATA
	m_pHightLight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HightLight"));
	m_pHightLight->SetupAttachment(m_pPlateMesh);
	m_pHightLight->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_pHightLight->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	m_pHightLight->SetHiddenInGame(true);
#endif
}

// Called when the game starts or when spawned
void ADAGDeskPlate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADAGDeskPlate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Реплицируем переменную Score
	DOREPLIFETIME(ADAGDeskPlate, m_bIsSelected);
	DOREPLIFETIME(ADAGDeskPlate, m_FPlateInfo);
}

void ADAGDeskPlate::SetPlateInfo(const FDAGPlateInfo& info)
{
	m_FPlateInfo = info;
}

void ADAGDeskPlate::Select()
{
	m_bIsSelected = true;
}

void ADAGDeskPlate::Deselect()
{
	m_bIsSelected = false;
}

void ADAGDeskPlate::OnRep_HighlightChanged()
{
	if (m_pHightLight)
	{
		m_pHightLight->SetHiddenInGame(!m_bIsSelected);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ADAGDeskPlate::OnRep_HighlightChanged: m_pHightlight is nullptr for actor %s!"), *GetName());
	}
}

