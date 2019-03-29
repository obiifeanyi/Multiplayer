// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "Public/Blueprint/UserWidget.h"
#include <Engine/Engine.h>
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include <ConstructorHelpers.h>

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"

const static FName SESSION_NAME =  TEXT("SimonSession");

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
		SessionInterface = SubSystem->GetSessionInterface();

		if(SessionInterface.IsValid())
		{
			//Make a delegate to execute a callback when a Session is created or destroy.
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,&UPuzzlePlatformGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionComplete);
			//Find session delegate and call a function when we finish finding all session.
			//Host triggers finding session
			//Another function is called on completion


			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch.IsValid())
			{
				SessionSearch->bIsLanQuery = true;
				SessionInterface->FindSessions(0,SessionSearch.ToSharedRef());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Online SubSystem not found"));
	}
}



//On Find Session
void UPuzzlePlatformGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Found"));
	if (bWasSuccessful && SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Search result is %s"), *SearchResult.GetSessionIdStr());
		}
	}
}

//Make a session
void UPuzzlePlatformGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{

		//Check if a session of a specific name exist
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			Create_A_Session();
		}
	}

}

void UPuzzlePlatformGameInstance::Create_A_Session()
{
	if (SessionInterface.IsValid()) 
	{
		FOnlineSessionSettings SimonSessionSettings;
		SimonSessionSettings.bIsLANMatch = true;
		SimonSessionSettings.NumPublicConnections = 2;
		SimonSessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, SESSION_NAME, SimonSessionSettings);
	}
}

//Creates a new session
void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool Successful)
{
	if (SessionInterface.IsValid())
	{
		Create_A_Session();
	}
	
}

//Teleport to work
void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool Successful)
{

	if (!Successful)
	{
		
		return;
	}

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
