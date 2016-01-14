// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PawnWithCamera.generated.h"

UCLASS()
class RUNNER_API APawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnWithCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void Zoom(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	void SprintOn();
	void SprintOff();

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere)
	float SprintSpeedFactor = 10.0f;
	UPROPERTY(EditAnywhere)
	float DelaySpringFactor = 0.025f;
	UPROPERTY(EditAnywhere)
	float DelayActorRotationFactor = 0.025f;
	UPROPERTY(EditAnywhere)
	UCurveVector* Curve;
	UCameraComponent* OurCamera;

private:
	FVector2D MovementInput;
	FVector2D CameraInput;
	FVector2D RandomInput;
	float ElapsedTime;
	float ZoomFactor;
	float SpringMoveStep;
	float ActorRotationStep;
	bool bZoomingIn;
	bool bSprintOn;

	void ZoomUpdate(float DeltaTime);
	void YawUpdate();
	void PitchUpdate();
	void MoveUpdate(float DeltaTime);
	void MakeStep(float DeltaTime);
	void MakeSprintStep(float sprintFactor, float DeltaTime);

};
