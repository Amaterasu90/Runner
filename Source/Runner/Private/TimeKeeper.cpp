// Fill out your copyright notice in the Description page of Project Settings.

#include "Runner.h"
#include "TimeKeeper.h"


// Sets default values
ATimeKeeper::ATimeKeeper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	CountdownText->bCastDynamicShadow = true;
	CountdownText->CastShadow = true;
	RootComponent = CountdownText;
}

// Called when the game starts or when spawned
void ATimeKeeper::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATimeKeeper::AdvanceTimer, 1.0f, true);
	
}

// Called every frame
void ATimeKeeper::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATimeKeeper::UpdateTimerDisplay() {
	CountdownText->SetText(FText::FromString(FString::FromInt(FMath::Max(CountdownTime, 0))));
}

void ATimeKeeper::AdvanceTimer() {
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1) {
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

void ATimeKeeper::CountdownHasFinished(){
	CountdownText->SetText(FText::FromString("GO!"));
}

