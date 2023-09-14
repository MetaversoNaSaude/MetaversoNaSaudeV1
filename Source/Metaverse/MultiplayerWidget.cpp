// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerWidget.h"
#include "Kismet/GameplayStatics.h"

void UMultiplayerWidget::OpenLobby()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/VRTemplate/Maps/MainMenu?listen");
	}
}

void UMultiplayerWidget::CallOpenLevel(const FString& Address)
{
	UGameplayStatics::OpenLevel(this, *Address);
}

void UMultiplayerWidget::CallClientTravel(const FString& Address)
{
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UMultiplayerWidget::ChangeMap(const FString& Map)
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				FString::Printf(TEXT("Map %s"), *Map)
			);
		}
		FString MapAddress = FString::Printf(TEXT("/Game/VRTemplate/Maps/%s"), *Map);
		World->ServerTravel(*MapAddress);
	}
}
