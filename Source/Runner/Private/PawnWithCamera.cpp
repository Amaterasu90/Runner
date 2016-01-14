// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "PawnWithCamera.h"


// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->AttachTo(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->AttachTo(CameraSpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick( float DeltaTime )
{
	{
		if (bZoomingIn) {
			ZoomFactor += DeltaTime / 0.5f;
		}
		else {
			ZoomFactor -= DeltaTime / 0.25f;
		}

		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		CameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}
	{
		FRotator NewRotation = CameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		CameraSpringArm->SetWorldRotation(NewRotation);
	}
	{
		if (!MovementInput.IsZero()) {
			MovementInput = MovementInput.GetSafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}

	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAction("Zoom In", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("Zoom Out", IE_Released, this, &APawnWithCamera::ZoomOut);
	InputComponent->BindAxis("Move Forward", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("Move Right", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("Camera Pitch", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("Camera Yaw", this, &APawnWithCamera::YawCamera);

	Super::SetupPlayerInputComponent(InputComponent);
}

void APawnWithCamera::MoveForward(float AxisValue) {
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue) {
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue) {
	CameraInput.X = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue) {
	CameraInput.Y = AxisValue;
}

void APawnWithCamera::ZoomIn() {
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut() {
	bZoomingIn = false;
}

