// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "SpawnMovementComponent.h"
#include "MotherActor.h"


// Sets default values
AMotherActor::AMotherActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = Box;
	Box->InitBoxExtent(FVector(20.0f, 20.0f, 20.0f));

	UBoxComponent* Box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box1->InitBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	Box1->RelativeLocation = FVector(100.0f, 0.0f, 0.0f);
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->InitSphereRadius(60.0f);
	SphereComponent->RelativeLocation = FVector(100.0f, 0.0f, 0.0f);
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded()) {
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	Box1->AttachTo(RootComponent);
	SphereVisual->AttachTo(RootComponent);
	SphereComponent->AttachTo(RootComponent);

	USpawnMovementComponent* spawn = CreateDefaultSubobject<USpawnMovementComponent>(TEXT("Spawner"));
	spawn->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AMotherActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMotherActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

