// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class RUNNER_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Rotation|Angles")
	float Alfa;
	UPROPERTY(EditAnywhere, Category = "Rotation|Angles")
	float Beta = 90;
	UPROPERTY(EditAnywhere, Category = "Rotation|Angles")
	float GammaRadians;
	UPROPERTY(EditAnywhere, Category = "Rotation|Radius")
	float Radius = 20.0f;
	UPROPERTY(EditAnywhere, Category = "Rotation|Speed")
	float SpeedFactor = 30.0f;

	// Sets default values for this actor's properties
	AFloatingActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	float ChangeToRadians(float randians);
	float Mod(float data, float boundary);
};
