// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "Public/Blueprint/UserWidget.h"
#include <Engine/Engine.h>


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenu (TEXT("/Game/Simon/MainMenu/WBP_MainMenu"));
	if (MainMenu.Class != NULL)
	{
		MainMenuBP = MainMenu.Class;
		UE_LOG(LogTemp, Warning, TEXT("UI_Widget is %s"),*MainMenuBP->GetName());
	}
}

void UPuzzlePlatformGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Initializer Called in GameInstance"));

}

void UPuzzlePlatformGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!Engine)return;
	Engine->AddOnScreenDebugMessage(0,5,FColor::Green,TEXT("Host code is called"));

	UWorld* World = GetWorld();
	if (!World)return;
	World->ServerTravel("/Game/Simon/Level/Lv_Stage");
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
	UUserWidget* Menu = CreateWidget(this, MainMenuBP);
	//add the widget to the screen
	if (!Menu)return;
	Menu->AddToViewport();

	//Setting the input mode so mouse is visible and button are focused on.
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController)return;
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);	
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}
