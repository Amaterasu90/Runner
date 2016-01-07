// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "OrbitalActor.h"

// Sets default values
AOrbitalActor::AOrbitalActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AOrbitalActor::BeginPlay()
{
	StartPosition = GetActorLocation();
	Super::BeginPlay();
	
}

// Called every frame
void AOrbitalActor::Tick( float DeltaTime )
{
	FVector NewLoaction = StartPosition;

	float x = NewLoaction.X;
	float y = NewLoaction.Y;
	float z = NewLoaction.Z;
	
	float dX = Radius * (FMath::Sin(ChangeToRadians(Alfa))*FMath::Sin(ChangeToRadians(Gamma)) - FMath::Cos(ChangeToRadians(Alfa))*FMath::Cos(ChangeToRadians(Beta))*FMath::Sin(ChangeToRadians(Gamma))+ FMath::Sin(ChangeToRadians(Beta))*FMath::Sin(ChangeToRadians(Gamma)));
	float dY = Radius * (FMath::Sin(ChangeToRadians(Alfa))*FMath::Sin(ChangeToRadians(Gamma)) + FMath::Cos(ChangeToRadians(Alfa))*FMath::Cos(ChangeToRadians(Beta))*FMath::Cos(ChangeToRadians(Gamma)) - FMath::Sin(ChangeToRadians(Beta))*FMath::Cos(ChangeToRadians(Gamma)));
	float dZ = Radius * (FMath::Cos(ChangeToRadians(Beta)) + FMath::Cos(ChangeToRadians(Alfa))*FMath::Sin(ChangeToRadians(Beta)));

	Alfa = Mod(Alfa + DeltaTime * SpeedFactor,360.0f);

	if (Alfa + DeltaTime * SpeedFactor > 360.0f){
		Beta = Mod(Beta + 3, 360.0f);
		Alfa = 0;
	}

	NewLoaction.X = x + dX;
	NewLoaction.Y = y + dY;
	NewLoaction.Z = z + dZ;
	SetActorLocation(NewLoaction);

	Super::Tick(DeltaTime);
}

float AOrbitalActor::ChangeToRadians(float degrees)
{
	return degrees * PI / 180.0f;
}

float AOrbitalActor::Mod(float data, float boundary)
{
	if (boundary > 0 && data / boundary > 1)
		return data - boundary;
	else
		return data;
}

