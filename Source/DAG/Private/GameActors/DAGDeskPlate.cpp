// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActors/DAGDeskPlate.h"

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

void ADAGDeskPlate::SetPlateInfo(const FDAGPlateInfo& info)
{
	m_FPlateInfo = info;
}

void ADAGDeskPlate::SetHightLight(bool bHightLight)
{
#if WITH_EDITORONLY_DATA
	m_pHightLight->SetHiddenInGame(!bHightLight);
	m_bIsSelected = bHightLight;
#endif
}

