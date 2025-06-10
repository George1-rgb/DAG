// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DAGTypes.generated.h"

UENUM()
enum class EPlateType
{
	kBase = 0,
	kField,
	kHeadPhone
};

UENUM()
enum class ECommandNum
{
	kBlue = 0,
	kGreen,
	kYellow,
	kRed
};

USTRUCT(BlueprintType)
struct FDAGPlateInfo
{
	GENERATED_BODY()

	FDAGPlateInfo() = default;
	FDAGPlateInfo(const double& fX, const double& fY, const double& fZ)
		: m_fX(fX), m_fY(fY), m_fZ(fZ)

	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double m_fX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double m_fY;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double m_fZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlateType m_ePlateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_nPlayerNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int m_nFieldNum = -1;
};

