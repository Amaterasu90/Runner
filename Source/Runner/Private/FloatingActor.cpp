// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "FloatingActor.h"


// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick( float DeltaTime )
{
	FVector NewLocation = GetActorLocation();

	float x = NewLocation.X;
	
	float dX = FMath::Sin(ChangeToRadians(Alfa));
	float dY = FMath::Cos(ChangeToRadians(Alfa))*FMath::Cos(ChangeToRadians(Beta)) - FMath::Sin(ChangeToRadians(Beta));
	float dZ = FMath::Cos(ChangeToRadians(Beta)) + FMath::Cos(ChangeToRadians(Alfa))*FMath::Sin(ChangeToRadians(Beta));

	Alfa = Mod(Alfa + DeltaTime * SpeedFactor,360.0f);

	if (Alfa + DeltaTime * SpeedFactor > 360.0f)
	{
		Alfa = 0;
		Beta = Mod(Beta + 3, 360.0f); ;
	}

	NewLocation.X = dX*Radius;
	NewLocation.Y = dY*Radius;
	NewLocation.Z = dZ*Radius;
	SetActorLocation(NewLocation);

	Super::Tick(DeltaTime);
}

float AFloatingActor::ChangeToRadians(float degrees)
{
	return degrees * PI / 180.0f;
}

float AFloatingActor::Mod(float data, float boundary)
{
	if (boundary > 0 && data / boundary > 1)
		return data - boundary;
	else
		return data;
}

