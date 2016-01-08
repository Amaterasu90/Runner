// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += FBlendCamera::TimeBetweenCameraChanges;

		//Find the actor that handles control for the local player.
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController) {
			CurrentCamera = Cameras[CurrentCameraIndex].Camera;
			if (CurrentCamera) {
				OurPlayerController->SetViewTargetWithBlend(CurrentCamera, FBlendCamera::SmoothBlendTime);
			}
			if (CurrentCameraIndex < Cameras.Num() - 1)
				CurrentCameraIndex++;
			else
				CurrentCameraIndex = 0;
		}
	}
}

