// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "OrbitalActor.generated.h"

UCLASS()
class RUNNER_API AOrbitalActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	FVector StartPosition;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Alfa;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Beta;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Gamma = 45.0f;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Radius = 20.0f;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float SpeedFactor = 250.0f;


	// Sets default values for this actor's properties
	AOrbitalActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	float ChangeToRadians(float randians);
	float Mod(float data, float boundary);
};
