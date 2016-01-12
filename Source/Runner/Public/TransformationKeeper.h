// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TransformationKeeper.generated.h"

UCLASS()
class RUNNER_API ATransformationKeeper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransformationKeeper();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	float XTransformDistance = 100.0f;

	UPROPERTY(EditAnywhere)
	float XTransformRatio = 1.0f;

	UPROPERTY(EditAnywhere)
	float CountdownTime = 3.0f;

	UPROPERTY(EditAnywhere)
	float DeltaTime = 0.1f;
	
	UPROPERTY(EditAnywhere)
	AActor* actor;

	FTimerHandle CountdownTimerHandle;
	UTextRenderComponent* CountdownText;
	bool bEventWasCalled;
	float factor = 1.0f;
	FVector OldLocation;
	FText message;
	
	void UpdateLocation();
	void UpdateDisplay();

	UFUNCTION(BlueprintNativeEvent)
	void StartTransformation();

	UFUNCTION(BlueprintNativeEvent)
	void StopTransformation();

	UFUNCTION(BlueprintNativeEvent)
	void FinishCoundown();

	void TimerDelegate();
};
