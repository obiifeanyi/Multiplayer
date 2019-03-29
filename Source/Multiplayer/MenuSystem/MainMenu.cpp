// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

#include "ServerRow.h"
#include <ConstructorHelpers.h>


UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/Simon/MainMenu/WBP_ServerRow"));
	if(ServerRowBPClass.Class != NULL)
	{
		UE_LOG(LogTemp,Warning,TEXT("Hello world"))
		ServerRowClass = ServerRowBPClass.Class;
	}
}

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
	
	if (GameInstanceToMenu != nullptr)
	{
		UWorld* World = this->GetWorld();
		if(!ensure(World != nullptr))return;

		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRowClass);
		if(!ensure (Row != nullptr))return;

		ServerList->AddChild(Row);
	}
}

void UMainMenu::HostServer()
{
	if (GameInstanceToMenu != nullptr)
	{
		GameInstanceToMenu->Host();
	}
}
