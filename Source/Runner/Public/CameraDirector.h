// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FBlendCamera.h"
#include "CameraDirector.generated.h"

UCLASS()
class RUNNER_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
private:
	UPROPERTY(EditAnywhere)
	TArray<FBlendCamera> Cameras;

	AActor* CurrentCamera;
	int CurrentCameraIndex;

	float TimeToNextCameraChange;
};
