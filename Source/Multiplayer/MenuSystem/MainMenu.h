// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuSystem.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UMainMenu : public UMenuSystem
{
	GENERATED_BODY()
	virtual bool Initialize() override;

	IMenuInterface* MenuInterface = nullptr;

public:

	UFUNCTION()
	void HostServer();	

protected:

	//UI binding properties
	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* BackToMainMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinConfirmButton;
	
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* SwitchMenus;

	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* IP_Login;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IpInput;

	//Menu Navigation functions
	UFUNCTION()
	void OpenJoinMenu();
	UFUNCTION()
	void BackToMainMenu();
	UFUNCTION()
	void JoinServer();
};
