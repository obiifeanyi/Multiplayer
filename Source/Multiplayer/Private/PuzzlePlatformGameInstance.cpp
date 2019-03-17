// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "Public/Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "OnlineSubsystem.h"
#include <Engine/Engine.h>


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	
	static ConstructorHelpers::FClassFinder<UMainMenu> MainMenu (TEXT("/Game/Simon/MainMenu/WBP_MainMenu"));
	if (MainMenu.Class != NULL)
	{
		MainMenuBP = MainMenu.Class;
	}
	static ConstructorHelpers::FClassFinder<UInGameMenu>InGameMenu(TEXT("/Game/Simon/MainMenu/WBP_InGameMenu"));
	if (InGameMenu.Class != NULL)
	{
		InGameMenuBP = InGameMenu.Class;
		
	}
}

void UPuzzlePlatformGameInstance::Init()
{
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (ensure(SubSystem != nullptr))
	{
		UE_LOG(LogTemp,Warning,TEXT("Online SubSystem found %s"), *SubSystem->GetSubsystemName().ToString());
		IOnlineSessionPtr SessionInterface = SubSystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Session was found"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Online SubSystem not found"));
	}
}

void UPuzzlePlatformGameInstance::Host()
{
	UWorld* World = GetWorld();
	if (!World)return;
	World->ServerTravel("/Game/Simon/Level/Lv_Stage?Listen");
	Menu->TearDown();
	
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!Engine)return;
	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Host code is called %s"), *Address));
	//use player controller to travel, use address input to travel
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	Menu->TearDown();
}

void UPuzzlePlatformGameInstance::LoadMenuWidget()
{
	if (!MainMenuBP)return;
	Menu = CreateWidget<UMainMenu>(this, MainMenuBP);
	if (!Menu)return;
	Menu->SetGameInstanceToMenuInterface(this);
	Menu->SetUp();
}

void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	
	InMenu = CreateWidget<UInGameMenu>(this,InGameMenuBP);
	InMenu->SetGameInstanceToMenuInterface(this);
	InMenu->SetUp();
}

void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	PlayerController->ClientTravel("/Game/Simon/Level/Lv_MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::CloseGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	PlayerController->ConsoleCommand("Exit");
}
