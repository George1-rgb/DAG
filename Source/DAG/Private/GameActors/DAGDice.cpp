// Fill out your copyright notice in the Description page of Project Settings.
#include "GameActors/DAGDice.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
ADAGDice::ADAGDice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
	smDice = CreateDefaultSubobject<UStaticMeshComponent>("DiceStaticMesh");
	SetRootComponent(smDice);
	smDice->SetSimulatePhysics(true);
	smDice->SetEnableGravity(true);
	smSphere1 = CreateDefaultSubobject<USphereComponent>("Sphere1SM");
	m_smSpheres.Add(smSphere1, 1);
	smSphere2 = CreateDefaultSubobject<USphereComponent>("Sphere2SM");
	m_smSpheres.Add(smSphere2, 2);
	smSphere3 = CreateDefaultSubobject<USphereComponent>("Sphere3SM");
	m_smSpheres.Add(smSphere3, 3);
	smSphere4 = CreateDefaultSubobject<USphereComponent>("Sphere4SM");
	m_smSpheres.Add(smSphere4, 4);
	smSphere5 = CreateDefaultSubobject<USphereComponent>("Sphere5SM");
	m_smSpheres.Add(smSphere5, 5);
	smSphere6 = CreateDefaultSubobject<USphereComponent>("Sphere6SM");
	m_smSpheres.Add(smSphere6, 6);

	for (auto pSphere : m_smSpheres)
	{
		pSphere.Key->SetSphereRadius(5.0);
		pSphere.Key->SetHiddenInGame(true);
		pSphere.Key->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		pSphere.Key->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		pSphere.Key->SetupAttachment(smDice);
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetIsReplicated(true); // Очень важно реплицировать компонент!

	// Настраиваем поведение компонента
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.6f;
	ProjectileMovement->Friction = 0.4f;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
}

bool ADAGDice::IsDiceStopping() const
{
	return smDice->GetComponentVelocity() == FVector(0.0, 0.0, 0.0);
}

int ADAGDice::GetValue()
{
	int nRes = 0;
	double fTempZ = -1.0e6;
	for (auto pSphere : m_smSpheres)
	{
		if (pSphere.Key->GetComponentLocation().Z > fTempZ)
		{
			nRes = pSphere.Value;
			fTempZ = pSphere.Key->GetComponentLocation().Z;
		}
	}
	return nRes;
}

// Called when the game starts or when spawned
void ADAGDice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADAGDice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if ()
		bIsStopping = true;*/
}

