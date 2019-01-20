// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"
#include "MovingBox.h"
#include <Components/BoxComponent.h>

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Volume trigger.
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!TriggerVolume)return;
	RootComponent = TriggerVolume;

	//Set event on overlap begin.
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	//set event on overlap end.
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (!ensure(MovingPlatforms.Last() != nullprt)) return;					 TODO find proper syntax for ensure
	
	if (MovingPlatforms.Num() == 0) return; //If null Bait out
	for (auto MovingPlatform:MovingPlatforms)
	{
		if (!MovingPlatform)return;
		MovingPlatform->AddToActiveTrigger();
	}
}

 void APlatformTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {

	// if (!ensure(MovingPlatforms.Last() != nullprt)) return;

	 if (MovingPlatforms.Num() == 0) return; //If null Bait out
	 for (auto MovingPlatform : MovingPlatforms)
	 {
		 if (!MovingPlatform)return;
		 MovingPlatform->RemoveFromActiveTrigger();
	 }
 }

