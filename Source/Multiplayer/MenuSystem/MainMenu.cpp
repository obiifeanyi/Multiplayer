// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Init = Super::Initialize();
	if (!Init) return false;
	if (!Host) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::SetUp()
{
	//Setting the input mode so mouse is visible and button are focused on.
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		if (!PlayerController)return;
		FInputModeUIOnly InputModeData;
		//InputModeData.SetWidgetToFocus(Menu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = true;
}


void UMainMenu::TearDown()
{
//Setting the input mode player can move around
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)return;
	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(true);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}