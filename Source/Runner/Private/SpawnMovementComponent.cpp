// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "SpawnMovementComponent.h"

USpawnMovementComponent::USpawnMovementComponent() {
	
}

void USpawnMovementComponent::BeginPlay() {
	UpdatedComponent->GetChildrenComponents(true,detachElements);
	CurrentCountDown = TimeCount;
}

void USpawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	CurrentCountDown = FMath::Clamp(CurrentCountDown, 0.0f, TimeCount) - DeltaTime;
	if (CurrentCountDown < DeltaTime && detachElements.Num() > counter) {
		CurrentCountDown = TimeCount;
		Unregister(detachElements[counter]);
		++counter;
	}
}

void USpawnMovementComponent::Unregister(USceneComponent* component) {
	if (component->GetAttachParent() == nullptr) {
		component->DestroyComponent(false);
	}
	if (component != nullptr && component->GetAttachParent() != nullptr) {
		component->DestroyComponent(true);
	}
	else
		return;
}
