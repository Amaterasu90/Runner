// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "OrbitalPawnMovementComponent.h"

void UOrbitalPawnMovementComponent::SetRotationRate(FRotator value) {
	_RotationRate = value;
}

void UOrbitalPawnMovementComponent::SetPivot(FVector value) {
	_Pivot = value;
}

void UOrbitalPawnMovementComponent::BeginPlay() {
	Super::BeginPlay();
	RotationRate = _RotationRate;
	PivotTranslation = _Pivot;
}

void UOrbitalPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}