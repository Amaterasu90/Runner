// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TimeKeeper.generated.h"

UCLASS()
class RUNNER_API ATimeKeeper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeKeeper();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void UpdateTimerDisplay();

	void CountdownHasFinished();

	void AdvanceTimer();

private:
	UPROPERTY(EditAnywhere)
	int32 CountdownTime = 3;
	UTextRenderComponent* CountdownText;
	FTimerHandle CountdownTimerHandle;
	
};
