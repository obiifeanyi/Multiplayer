// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


bool UMainMenu::Initialize()
{
	bool Init = Super::Initialize();
	if (!Init) return false;
	if (!HostButton) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	BackToMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMainMenu);
	JoinConfirmButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}

//Press join button opens Join Menu
void UMainMenu::OpenJoinMenu()
{
	//UE_LOG(LogTemp,Warning,TEXT("Clicking Button"))
	SwitchMenus->SetActiveWidget(IP_Login);
}

void UMainMenu::BackToMainMenu()
{
	//UE_LOG(LogTemp,Warning,TEXT("Clicking Button"))
	SwitchMenus->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	const FString Address = IpInput->GetText().ToString();

	if (GameInstanceToMenu != nullptr)
	{
		GameInstanceToMenu->Join(Address);
	}
}

void UMainMenu::HostServer()
{
	if (GameInstanceToMenu != nullptr)
	{
		GameInstanceToMenu->Host();
	}
}
