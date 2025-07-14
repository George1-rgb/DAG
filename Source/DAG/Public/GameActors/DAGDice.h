// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DAGDice.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class DAG_API ADAGDice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADAGDice();
	bool IsDiceStopping() const;
	int GetValue();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* smDice;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* smSphere1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* smSphere2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* smSphere3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* smSphere4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* smSphere5;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* smSphere6;

	// ��������� ��� ��������
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* ProjectileMovement;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	bool bIsStopping = false;
	TMap<USphereComponent*, int> m_smSpheres;
};
