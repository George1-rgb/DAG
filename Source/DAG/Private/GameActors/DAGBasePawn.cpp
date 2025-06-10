// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActors/DAGBasePawn.h"
#include "GameActors/DAGBasePawnController.h"
#include "Engine/Engine.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/DamageType.h"
#include "GameModes/DAGGameMode.h"
#include "GameModes/DAGGameStateBase.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADAGBasePawn::ADAGBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	smRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(smRoot);

	smPawn = CreateDefaultSubobject<UStaticMeshComponent>("DiceStaticMesh");
	smPawn->SetupAttachment(smRoot);
	
	smPawn->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	smPawn->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	smPawn->SetGenerateOverlapEvents(true);

	smHighlight = CreateDefaultSubobject<UStaticMeshComponent>("Highlight");
	smHighlight->SetupAttachment(smPawn);
	smHighlight->SetHiddenInGame(true);

	smCollision = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	smCollision->InitSphereRadius(5.0f);
	smCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	smCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	smCollision->bReturnMaterialOnMove = true;
	smCollision->SetupAttachment(smPawn);
}

// Called when the game starts or when spawned
void ADAGBasePawn::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &ADAGBasePawn::OnTakeDamage);
	//smCollision->OnComponentBeginOverlap.AddDynamic(this, &ADAGBasePawn::OnCollisionComponentOverlap);
}

void ADAGBasePawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADAGBasePawn, m_bIsHighlighted);
}

void ADAGBasePawn::OnRep_HighlightChanged()
{
	smHighlight->SetHiddenInGame(!m_bIsHighlighted);
}

// Called every frame
void ADAGBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!m_bMoving)
		return;

	m_fElapsedTime += DeltaTime;
	float Alpha = FMath::Clamp(m_fElapsedTime / m_fMovingDuration, 0.0f, 1.0f);

	FVector NewLocation = FMath::Lerp(GetActorLocation(), m_vTargetPos, Alpha);
	SetActorLocation(NewLocation);

	if (Alpha >= 1.0f)
	{
		m_bMoving = false;
		m_fElapsedTime = 0.0f;
		smCollision->SetGenerateOverlapEvents(false);
	}
}

// Called to bind functionality to input
void ADAGBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADAGBasePawn::OnPawnClicked()
{
	if (HasAuthority())
	{
		m_bIsHighlighted = true;
		OnRep_HighlightChanged();  // чтобы сразу обновить сервер и хост
	}
}

void ADAGBasePawn::Deselect()
{
	if (HasAuthority())
	{
		m_bIsHighlighted = false;
		OnRep_HighlightChanged();  // чтобы сразу обновить сервер и хост
	}
}

void ADAGBasePawn::SetNewActorLocation(const FVector& vNewPos)
{
	smCollision->SetGenerateOverlapEvents(false);
	m_vTargetPos = vNewPos;
	m_bMoving = true;
}

void ADAGBasePawn::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//auto pOtherPawn = Cast<ADAGBasePawn>(DamageCauser);
	//smHighlight->SetHiddenInGame(false);
	Destroy();
}

void ADAGBasePawn::OnCollisionComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!GetWorld())
		return;

	ADAGGameStateBase* GS = GetWorld()->GetGameState<ADAGGameStateBase>();
	if (!GS)
		return;
	auto pOtherPawn = Cast<ADAGBasePawn>(OtherActor);
	if (!pOtherPawn || pOtherPawn == this || GS->m_pCurrentSelPawn != this)
		return;

	UGameplayStatics::ApplyPointDamage(pOtherPawn, 100.0, FVector(), SweepResult, GetController(), this, m_DamageType);
}

