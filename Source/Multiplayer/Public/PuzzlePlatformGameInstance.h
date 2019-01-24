// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UPuzzlePlatformGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init() override;
	
	TSubclassOf<class UUserWidget> MainMenuBP;

public:

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& Address);

	UFUNCTION(BlueprintCallable)
		void LoadMenu();


	
	
};
