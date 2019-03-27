// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSessionInterface.h"
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
	TSubclassOf<class UInGameMenu> InGameMenuBP;

	UMainMenu* Menu;
	UInGameMenu* InMenu; //Should this be a global property.

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

public:

	UFUNCTION(Exec)
		void Host() override;

	UFUNCTION(Exec)
		void Join(const FString& Address) override;

	UFUNCTION(BlueprintCallable)
		void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
		void LoadInGameMenu();

	UFUNCTION(Exec)
		void CloseGame() override; //Exit the whole game.
	
	void LoadMainMenu();

	void Create_A_Session();
	void OnCreateSessionComplete(FName SessionName, bool Successful);
	void OnDestroySessionComplete(FName SessionName, bool Successful);
	void OnFindSessionComplete(bool bWasSuccessful);
	
};