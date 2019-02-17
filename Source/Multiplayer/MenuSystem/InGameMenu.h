// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UInGameMenu : public UMenuSystem
{
	GENERATED_BODY()

protected:

	virtual bool Initialize() override;
	
	//Button Binding
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton;

	UFUNCTION()
	void CloseMenu();

	UFUNCTION()
	void QuitLevel();

	UFUNCTION()
	void ExitGamePressed();


};
