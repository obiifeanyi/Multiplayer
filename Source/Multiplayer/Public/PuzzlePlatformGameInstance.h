// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
private:
	UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init() override;
	
	TSubclassOf<class UMainMenu> MainMenuBP;

	UMainMenu* Menu;

public:

	UFUNCTION(Exec)
		void Host() override;

	UFUNCTION(Exec)
		void Join(const FString& Address);

	UFUNCTION(BlueprintCallable)
		void LoadMenu();


	
	
};
