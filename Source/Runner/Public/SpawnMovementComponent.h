// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "SpawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API USpawnMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
public:
	USpawnMovementComponent();
	void Unregister(USceneComponent* component);
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
private:
	TArray<USceneComponent*> detachElements;
	float TimeCount = 3.0f;
	float CurrentCountDown;
	int counter;
};
