// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TorchKeeper.generated.h"

UCLASS()
class RUNNER_API ATorchKeeper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorchKeeper();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	//Event
	UFUNCTION(BlueprintNativeEvent)
	void AddFuel();
	//Event
	UFUNCTION(BlueprintNativeEvent)
	void DouseWithFire();

	void Update();

private:
	UPROPERTY(EditAnywhere)
	int StartStamina = 100;
	UPROPERTY(EditAnywhere)
	int TimeToSplashWater = 200;
	int CurrentStamina;
	int CurrentTimeToSpashWater;
	FTimerHandle TimerHandle;
	bool bWet;
	UParticleSystemComponent* particleSystemPtr;

	void SplashCounting();
	void FuelCounting();
};
