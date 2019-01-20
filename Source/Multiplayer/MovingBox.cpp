// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingBox.h"



AMovingBox::AMovingBox()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingBox::BeginPlay()
{
	Super::BeginPlay();
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);


	//Set Replication
	if (HasAuthority())
	{
	SetReplicates(true);
	SetReplicateMovement(true);
	}
}

void AMovingBox::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (NumberActiveTrigger > 0)
	{
	PlatformMovenment(DeltaSeconds);
	}
}

void AMovingBox::PlatformMovenment(float DeltaSeconds)
{
//Moving the box
	FVector Location = GetActorLocation();
	// switching th start and target location based on vector magnitude to target		//magnitude of distance
	float JourneyLength = (GlobalStartLocation - Location).Size();
	float TargetDistanceLength = (GlobalTargetLocation - GlobalStartLocation).Size();

	if (JourneyLength >= TargetDistanceLength)
	{
		FVector HolderFor = GlobalStartLocation;
		GlobalStartLocation = GlobalTargetLocation;
		GlobalTargetLocation = HolderFor;
	}

	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
	Location += (Speed * DeltaSeconds * Direction);
	SetActorLocation(Location);
}

void AMovingBox::AddToActiveTrigger()
{
	NumberActiveTrigger++;
}
void AMovingBox::RemoveFromActiveTrigger()
{
	if (NumberActiveTrigger > 0)
	{
		NumberActiveTrigger--;
	}
}