// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "TransformationKeeper.h"


// Sets default values
ATransformationKeeper::ATransformationKeeper() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	CountdownText->SetText(TEXT("Timer"));
	CountdownText->bCastDynamicShadow = true;
	CountdownText->CastShadow = true;
	RootComponent = CountdownText;
	CountdownTimeCounter = CountdownTime;
}


void ATransformationKeeper::TimerDelegate() {
	if(CountdownTimeCounter > 0)
		CountdownTimeCounter -= DeltaTime;
	UpdateDisplay();
	if (CountdownTimeCounter < DeltaTime) {
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATransformationKeeper::LocationDelegate, DeltaTime, true);
		FinishCoundown();
		StartTransformation();
	}
}

void ATransformationKeeper::LocationDelegate() {
	UpdateDisplay();
	UpdateLocation();
}

void ATransformationKeeper::FinishCoundown_Implementation() {
	message = FText::FromString("Finish Counting!");
}

void ATransformationKeeper::UpdateDisplay() {
	float time = CountdownTimeCounter - (float)FMath::Floor(CountdownTimeCounter);
	float result = FMath::Floor(CountdownTimeCounter) + FMath::Floor(time*10.0f)/10.0f ;
	if(result > 0.0f)
		message = FText::FromString(FString::SanitizeFloat(FMath::Max(result, 0.0f)));
	CountdownText->SetText(message);
}

void ATransformationKeeper::StartTransformation_Implementation() {
		message = FText::FromString("Increment sequence!");
}

void ATransformationKeeper::StopTransformation_Implementation() {
		message = FText::FromString("Decrement sequence!");
}

void ATransformationKeeper::UpdateLocation() {
	FVector newLocation = actor->GetActorLocation();
	float displacement = factor * XTransformRatio;
	newLocation.X += displacement;
	
	if (newLocation.X > OldLocation.X + XTransformDistance) {
		factor = -1.0f;
		StopTransformation();
	} else if (newLocation.X < OldLocation.X) {
		factor = 1.0f;
		StartTransformation();
	}
	actor->SetActorLocation(newLocation);
}

// Called when the game starts or when spawned
void ATransformationKeeper::BeginPlay() {
	Super::BeginPlay();
	OldLocation = actor->GetActorLocation();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATransformationKeeper::TimerDelegate, DeltaTime, true);
}

// Called every frame
void ATransformationKeeper::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

