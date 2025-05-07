// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActors/DAGDesk.h"
#include "GameActors/DAGDeskPlate.h"
#include "Kismet/GameplayStatics.h"
#include "Global/DAGTypes.h"

// Sets default values
ADAGDesk::ADAGDesk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ADAGDesk::BuildDesk(const FVector vLocation, const int nX, const int nY)
{
	if (m_vPlates.Num() == 0)
	{
		m_vDeskSize.X = nX;
		m_vDeskSize.Y = nY;

		for (int i = 0; i <= nY - 1; ++i)
		{
			for (int j = 0; j <= nX - 1; ++j)
			{
				constexpr double fPlateSize = 100.0;

				FVector vSpawnLocation = FVector(static_cast<double>(j) - static_cast<double>(nX) / 2.f, 
												 static_cast<double>(i) - static_cast<double>(nY) / 2.f,
												 0.f)
												 * fPlateSize
												 * 1.f
												 + vLocation;
				FTransform vSpawnTransform;
				vSpawnTransform.SetLocation(vSpawnLocation);
				if (m_cPlateClass)
				{
					AActor* pPlateToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, m_cPlateClass.LoadSynchronous(), vSpawnTransform);
					ADAGDeskPlate* pPlate = Cast<ADAGDeskPlate>(pPlateToSpawn);
					if (pPlate)
					{
						pPlate->SetPlateInfo(FDAGPlateInfo(static_cast<double>(j), static_cast<double>(i), 0.f));
					}

					pPlateToSpawn->FinishSpawning(vSpawnTransform);
					m_vPlates.Add(pPlateToSpawn);
					pPlateToSpawn->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ADAGDesk::BeginPlay()
{
	Super::BeginPlay();
	
}

