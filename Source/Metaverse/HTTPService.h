// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <HttpModule.h>
#include "HTTPService.generated.h"

USTRUCT()
struct FLoginData {
	GENERATED_BODY()
		UPROPERTY()
		int status;
	UPROPERTY()
		FString name;
	UPROPERTY()
		FString hash;
	UPROPERTY()
		int totalkills;
	UPROPERTY()
		int totaldeaths;
};

USTRUCT()
struct FLoginRequest {
	GENERATED_BODY()

	UPROPERTY()
		FString email;
	UPROPERTY()
		FString password;
};

USTRUCT()
struct FLoginResponse {
	GENERATED_BODY()

	UPROPERTY()
		FLoginData LoginResult;
};

UCLASS()
class METAVERSE_API AHTTPService : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHTTPService();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FHttpModule* Http;

	FString APIBaseUrl;

	TSharedRef<IHttpRequest> RequestWithRoute(FString Subroute);

	TSharedRef<IHttpRequest> GetRequest(FString Subroute);

	TSharedRef<IHttpRequest> PostRequest(FString Subroute, FString ContentJsonString);

	void OnGetUsersResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void Send(TSharedRef<IHttpRequest>& Request);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
