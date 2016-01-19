// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "SpinMovementComponent.h"

void USpinMovementComponent::BeginPlay() {
	Super::BeginPlay();
}

void USpinMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MoveUpdatedComponent(FVector::ZeroVector, _CurrentRotation, false);
	_CurrentRotation = _CurrentRotation.Clamp() + FRotator(0.0f, 100.0f, 0.0f) * DeltaTime;
}

