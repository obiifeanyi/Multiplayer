// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "Public/Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include <Engine/Engine.h>


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	
	static ConstructorHelpers::FClassFinder<UMainMenu> MainMenu (TEXT("/Game/Simon/MainMenu/WBP_MainMenu"));
	if (MainMenu.Class != NULL)
	{
		MainMenuBP = MainMenu.Class;
	}

}

void UPuzzlePlatformGameInstance::Init()
{
	
}

void UPuzzlePlatformGameInstance::Host()
{
// 	UEngine* Engine = GetEngine();
// 	if (!Engine)return;
// 	Engine->AddOnScreenDebugMessage(0,5,FColor::Green,TEXT("Host code is called"));

	UWorld* World = GetWorld();
	if (!World)return;
	World->ServerTravel("/Game/Simon/Level/Lv_Stage");
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
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	//create the widget
	if (!MainMenuBP)return;
	Menu = CreateWidget<UMainMenu>(this, MainMenuBP);
	if (!Menu)return;

	Menu->AddToViewport();
	Menu->SetMenuInterface(this); //GameInstance tell Menu where to get interface. (this) is used since it can mutate into an interface.
	Menu->SetUp();
}
