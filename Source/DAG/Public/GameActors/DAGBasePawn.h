// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Global/DAGTypes.h"
#include "DAGBasePawn.generated.h"

class USceneComponent;
class USphereComponent;
class UDamageType;
UCLASS()
class DAG_API ADAGBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADAGBasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* smRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* smPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* smHighlight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* smCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageType> m_DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving")
	float m_fMovingDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command")
	ECommandNum m_eCommandNum = ECommandNum::kBlue;
	
	UPROPERTY(ReplicatedUsing = OnRep_HighlightChanged)
	bool m_bIsHighlighted = false;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	UFUNCTION()
	void OnRep_HighlightChanged();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void OnPawnClicked();
	void Deselect();
	void SetNewActorLocation(const FVector& vNewPos);
	const ECommandNum& GetCommandNum() const { return m_eCommandNum; }
	TSubclassOf<UDamageType> GetDamageType() const { return m_DamageType; }
private:
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
	UFUNCTION()
	void OnCollisionComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult& SweepResult);

	FVector m_vTargetPos;
	bool m_bMoving = false;
	float m_fElapsedTime = 0.0f;
};
