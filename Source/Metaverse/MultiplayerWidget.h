// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UMultiplayerWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void OpenLobby();

	UFUNCTION(BlueprintCallable)
	void CallOpenLevel(const FString& Address);

	UFUNCTION(BLueprintCallable)
	void CallClientTravel(const FString& Address);

	UFUNCTION(BLueprintCallable)
	void ChangeMap(const FString& Address);
};
