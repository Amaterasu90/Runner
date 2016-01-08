// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FBlendCamera.generated.h"

USTRUCT(BlueprintType)
struct FBlendCamera
{
	GENERATED_USTRUCT_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	AActor* Camera;
	static const float TimeBetweenCameraChanges;
	static const float SmoothBlendTime;
};
