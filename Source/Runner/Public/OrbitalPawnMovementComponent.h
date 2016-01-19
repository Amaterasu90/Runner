// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/RotatingMovementComponent.h"
#include "OrbitalPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API UOrbitalPawnMovementComponent : public URotatingMovementComponent
{
	GENERATED_BODY()
public:
	void SetRotationRate(FRotator value);
	void SetPivot(FVector value);
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
private:
	FRotator _RotationRate;
	FVector _Pivot;
	FQuat StartRotation;
	float elapsedTime;
};
