// Fill out your copyright notice in the Description page of Project Settings.


#include <Interfaces/IHttpResponse.h>
#include "HTTPService.h"

// Sets default values
AHTTPService::AHTTPService()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	APIBaseUrl = TEXT("http://10.176.0.95:5000/ferramenta");

}



// Called every frame
void AHTTPService::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSharedRef<IHttpRequest> AHTTPService::RequestWithRoute(FString Subroute)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetURL(APIBaseUrl + Subroute);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	return Request;

}

TSharedRef<IHttpRequest> AHTTPService::GetRequest(FString Subroute)
{

	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;

}

void AHTTPService::Send(TSharedRef<IHttpRequest> &Request)
{
	Request->ProcessRequest();
}

bool AHTTPService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful)
{
	if ((!bWasSuccessful) || (!Response.IsValid())) {
		return false;
	}
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code:  %d"), Response->GetResponseCode());
		return false;
	}
}

void AHTTPService::OnGetUsersResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	if (Response->GetResponseCode() == 200)
	{
		const FString ResponseBody = Response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("Making request to http://10.176.0.95:5000/ferramenta"));


		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			FString name = JsonArray[0]->AsObject()->GetStringField("NOME");
			FString description = JsonArray[0]->AsObject()->GetStringField("DESCRICAO_FERRAMENTA");

			UE_LOG(LogTemp, Warning, TEXT("Response:  Name: %s, Description: %s"), *name, *description);
			
		}
	}
}

// Called when the game starts or when spawned
void AHTTPService::BeginPlay() {
	Super::BeginPlay();
	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = GetRequest("");
	Request->OnProcessRequestComplete().BindUObject(this, &AHTTPService::OnGetUsersResponse);
	Send(Request);
}

