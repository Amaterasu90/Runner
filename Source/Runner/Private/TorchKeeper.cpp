// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "TorchKeeper.h"


// Sets default values
ATorchKeeper::ATorchKeeper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UParticleSystem> ArbitraryParticleName(TEXT("ParticleSystem'/Game/TutorialParticleSystem.TutorialParticleSystem'"));
	particleSystemPtr = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ArbitraryParticleName"));

	if (ArbitraryParticleName.Succeeded()) {
		particleSystemPtr->Template = ArbitraryParticleName.Object;
		particleSystemPtr->bVisible = false;
	}

	RootComponent = particleSystemPtr;
}

void ATorchKeeper::SplashCounting() {
	if (CurrentTimeToSpashWater > 0)
		--CurrentTimeToSpashWater;
	if (CurrentTimeToSpashWater < 1)
		DouseWithFire();
}

void ATorchKeeper::FuelCounting(){
	if (CurrentStamina > 0) {
		float ratio = (float)CurrentStamina / (float)StartStamina;
		particleSystemPtr->RelativeScale3D = FVector(ratio, ratio, ratio);
		--CurrentStamina;
	}
	if (CurrentStamina < 1)
		AddFuel();
}

void ATorchKeeper::Update(){
	SplashCounting();
	FuelCounting();
	
	if(CurrentTimeToSpashWater == 0 && CurrentStamina == 0)
		GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ATorchKeeper::DouseWithFire_Implementation() {
	UE_LOG(MyLogCat, Log, TEXT("DouseWithFire was called"));
	CurrentStamina = 0;
	bWet = true;
	particleSystemPtr->Deactivate();
}

void ATorchKeeper::AddFuel_Implementation() {
	UE_LOG(MyLogCat, Log, TEXT("AddFuel was called"));
	UE_LOG(MyLogCat, Log, TEXT("IsWet = %s"), bWet ? TEXT("true") : TEXT("false"));
	if(!bWet) {
		int step = 10;
		UE_LOG(MyLogCat, Log, TEXT("Stamina increment %d"), step);
		CurrentStamina += step;
	}
}

// Called when the game starts or when spawned
void ATorchKeeper::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = StartStamina;
	CurrentTimeToSpashWater = TimeToSplashWater;
	if (StartStamina > 0 && CurrentTimeToSpashWater > 0)
		particleSystemPtr->bVisible = true;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATorchKeeper::Update, 1.0f, true);
}

// Called every frame
void ATorchKeeper::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



