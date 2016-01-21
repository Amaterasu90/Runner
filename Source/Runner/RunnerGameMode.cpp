// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "RunnerGameMode.h"

void ARunnerGameMode::BeginPlay() {
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void ARunnerGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}

void ARunnerGameMode::AddMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (NewWidget != nullptr) {
		NewWidget->RemoveFromViewport();
		NewWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		NewWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (NewWidget != nullptr) {
			NewWidget->AddToViewport();
		}
	}
}