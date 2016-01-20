// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "CollidingPawn.h"
#include "OrbitalPawnMovementComponent.h"
#include "SpawnMovementComponent.h"
#include "SpinMovementComponent.h"
#include "OrbitalActor.h"


// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded()) {
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f,0.0f,-40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	ParticleComponent->AttachTo(SphereVisual);
	ParticleComponent->bAutoActivate = false;
	ParticleComponent->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded()) {
		ParticleComponent->SetTemplate(ParticleAsset.Object);
	}

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.0f, 0.0f, 0.0f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	UOrbitalPawnMovementComponent* Actor = CreateDefaultSubobject<UOrbitalPawnMovementComponent>(TEXT("OrbitalMovementComponent"));

	USceneComponent* orbitalFrag = CreateDefaultSubobject<USceneComponent>(TEXT("OrbitalWorld"));
	orbitalFrag->AttachTo(RootComponent);

	UStaticMeshComponent* OrbitalSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbitalVisualRepresentation"));
	OrbitalSphere->AttachTo(orbitalFrag);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> OrbitalSphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	FVector displacement = FVector(0, 180.0f, 0);
	if (OrbitalSphereVisualAsset.Succeeded()) {
		OrbitalSphere->SetStaticMesh(OrbitalSphereVisualAsset.Object);
	}

	orbitalFrag->SetRelativeLocation(displacement);

	FRotator rotationRate = FRotator(0.0f, -80.0f, 0.0f);
	Actor->SetRotationRate(rotationRate);
	Actor->SetPivot(-displacement);
	Actor->UpdatedComponent = orbitalFrag;

	USpinMovementComponent* Actor1 = CreateDefaultSubobject<USpinMovementComponent>(TEXT("SpinMovementComponent"));
	Actor1->UpdatedComponent = OrbitalSphere;

	/*USpawnMovementComponent* a = CreateDefaultSubobject<USpawnMovementComponent>(TEXT("FOO"));
	a->UpdatedComponent = SphereComponent;*/
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);

	InputComponent->BindAxis("Move Forward", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("Move Right", this, &ACollidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const {
	return MovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue) {
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent)) {
		MovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue) {
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent)) {
		MovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue) {
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle() {
	if (ParticleComponent && ParticleComponent->Template) {
		ParticleComponent->ToggleActive();
	}
}