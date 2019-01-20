// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingBox.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API AMovingBox : public AStaticMeshActor
{
	GENERATED_BODY()
	


private:

	//functions
	AMovingBox ();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//
	void PlatformMovenment(float DeltaSeconds);


	//Variable
	FVector	GlobalStartLocation;
	FVector	GlobalTargetLocation;

	//Uproperties
	UPROPERTY(EditAnywhere)
	float Speed = 100.0f;
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;
	UPROPERTY(EditAnywhere)
	int32 NumberActiveTrigger = 1;

public:
	void AddToActiveTrigger();
	void RemoveFromActiveTrigger();
	
	
};