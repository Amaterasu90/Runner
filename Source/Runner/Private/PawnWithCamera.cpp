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
void APawnWithCamera::BeginPlay() {
	Super::BeginPlay();
}

void APawnWithCamera::ZoomUpdate(float DeltaTime) {
	if (bZoomingIn) {
		ZoomFactor += DeltaTime / 0.5f;
	}

	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	CameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
}

void APawnWithCamera::YawUpdate() {
	FRotator NewRotation = GetActorRotation();
	ActorRotationStep = FMath::Clamp<float>(ActorRotationStep + CameraInput.X * DelayActorRotationFactor , -100.0f, 100.0f);
	NewRotation.Yaw += ActorRotationStep ;
	SetActorRotation(NewRotation);
}

void APawnWithCamera::PitchUpdate() {
	FRotator NewRotation = CameraSpringArm->GetComponentRotation();
	SpringMoveStep = FMath::Clamp<float>(SpringMoveStep + CameraInput.Y * DelaySpringFactor, -1.0f, 1.0f);
	NewRotation.Pitch = FMath::Clamp<float>(NewRotation.Pitch + SpringMoveStep, -80.0f, -15.0f);
	NewRotation.Pitch += RandomInput.X * 0.25f;
	NewRotation.Yaw += RandomInput.Y * 0.25f;
	CameraSpringArm->SetWorldRotation(NewRotation);
}

void APawnWithCamera::MoveUpdate(float DeltaTime) {
	if (!MovementInput.IsZero()) {
		if (bSprintOn)
			MakeSprintStep(SprintSpeedFactor,DeltaTime);
		else 
			MakeStep(DeltaTime);
	}
}

void APawnWithCamera::MakeSprintStep(float sprintFactor, float DeltaTime){
	MovementInput = MovementInput.GetSafeNormal() * 100.0f;
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * sprintFactor * MovementInput.X * DeltaTime;
	NewLocation += GetActorRightVector() * sprintFactor * MovementInput.Y * DeltaTime;
	SetActorLocation(NewLocation);
}

void APawnWithCamera::MakeStep(float DeltaTime) {
	MakeSprintStep(1.0f, DeltaTime);
}

// Called every frame
void APawnWithCamera::Tick( float DeltaTime )
{
	if (ElapsedTime + DeltaTime > 2.0f)
		ElapsedTime = 0.0f;
	else
		ElapsedTime += DeltaTime;
	RandomInput = FVector2D(Curve->GetVectorValue(ElapsedTime).X, Curve->GetVectorValue(ElapsedTime).Y);
	ZoomUpdate(DeltaTime);
	YawUpdate();
	PitchUpdate();
	MoveUpdate(DeltaTime);
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
	InputComponent->BindAction("Sprint On", IE_Pressed, this, &APawnWithCamera::SprintOn);
	InputComponent->BindAction("Sprint Off", IE_Released, this, &APawnWithCamera::SprintOff);
	InputComponent->BindAxis("Zoom", this, &APawnWithCamera::Zoom);

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

void APawnWithCamera::SprintOn() {
	bSprintOn = true;
}

void APawnWithCamera::SprintOff() {
	bSprintOn = false;
}

void APawnWithCamera::Zoom(float AxisValue) {
}

