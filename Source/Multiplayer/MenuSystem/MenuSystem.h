// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UMenuSystem : public UUserWidget
{
	GENERATED_BODY()
	
	//connection to send data out with (Interface)
protected:
	class IMenuInterface* GameInstanceToMenu = nullptr;

public:
	void SetUp();
	void TearDown();
	void SetGameInstanceToMenuInterface (class IMenuInterface* Interface);
	
private:
};
