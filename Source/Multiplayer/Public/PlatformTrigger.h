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
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<class AMovingBox*> MovingPlatforms;

private:
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

 	UFUNCTION()
 		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
