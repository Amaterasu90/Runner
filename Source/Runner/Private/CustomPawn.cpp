// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "CustomPawn.h"


// Sets default values
ACustomPawn::ACustomPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ACustomPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomPawn::Tick( float DeltaTime )
{
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing) {
		CurrentScale += DeltaTime;
	}
	else {
		CurrentScale -= DeltaTime;
	}

	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void ACustomPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAction("Grow", IE_Pressed, this, &ACustomPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &ACustomPawn::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &ACustomPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ACustomPawn::Move_YAxis);

	Super::SetupPlayerInputComponent(InputComponent);
}

void ACustomPawn::Move_XAxis(float AxisValue){
	if (!AxisValue == 0.0f)
		Acceleration.X += 10.0f;
	else
		Acceleration.X = 1.0f;
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Acceleration.X;
}

void ACustomPawn::Move_YAxis(float AxisValue){
	if (!AxisValue == 0.0f)
		Acceleration.Y += 10.0f;
	else
		Acceleration.Y = 1.0f;
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Acceleration.Y;
}

void ACustomPawn::StartGrowing() {
	bGrowing = true;
}

void ACustomPawn::StopGrowing() {
	bGrowing = false;
}

