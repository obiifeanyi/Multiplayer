// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "MenuInterface.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool Init = Super::Initialize();
	if(!ensure(Init)) return false;

	CancelButton->OnClicked.AddDynamic(this,&UInGameMenu::CloseMenu);
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitLevel);
	ExitGameButton->OnClicked.AddDynamic(this, &UInGameMenu::ExitGamePressed);
	return true;
}

void UInGameMenu::CloseMenu()
{
	TearDown();
}

void UInGameMenu::QuitLevel()
{
	if(!ensure(GameInstanceToMenu))return;
	GameInstanceToMenu->LoadMainMenu();
}

void UInGameMenu::ExitGamePressed()
{
	if (!ensure(GameInstanceToMenu))return;
	GameInstanceToMenu->CloseGame();
}