// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UButton* Host;

	UPROPERTY(meta = (BindWidget))
		class UButton* Join;

	virtual bool Initialize() override;

	IMenuInterface* MenuInterface = nullptr;

public:

	UFUNCTION()
	void HostServer();

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void SetUp();

	void TearDown();

};
