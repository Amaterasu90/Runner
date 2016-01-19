// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "SpinMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API USpinMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
private:
	FRotator _CurrentRotation;
};
