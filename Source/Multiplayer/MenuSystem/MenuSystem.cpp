// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuSystem.h"
#include "MenuInterface.h"


void UMenuSystem::SetGameInstanceToMenuInterface(IMenuInterface* Interface)
{
	GameInstanceToMenu = Interface;
}

	//Setting the input mode so mouse is visible and button are focused on.
void UMenuSystem::SetUp()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)return;
	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
	AddToViewport();
}


//Setting the input mode player can move around
void UMenuSystem::TearDown()
{
	
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)return;
	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(true);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
	RemoveFromViewport();
}

