// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformTrigger.generated.h"

//class UBoxComponent;


UCLASS()
class MULTIPLAYER_API APlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APlatformTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//
	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerVolume;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
