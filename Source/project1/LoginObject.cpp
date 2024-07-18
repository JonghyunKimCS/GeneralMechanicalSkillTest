<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginObject.h"
#include "GameFramework/RootMotionSource.h"
#include "GameFramework/PlayerController.h"

ULoginObject::ULoginObject() {
	HttpModule = &FHttpModule::Get();
}

void ULoginObject::ExecuteLogin(FString id, FString password)
{
	/*TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule->CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	HttpRequest->SetURL("http://165.132.107.24:8000/accounts/login/");
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginObject::HttpRequestFinishedDelegate);
	HttpRequest->ProcessRequest();*/
}

void ULoginObject::HttpRequestFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSccessful) 
{
	if (bWasSccessful) {
		GLog->Log("Hey we received the following response!");
	}
	//�������κ��� ����� ������ ȭ�鿡 ����� ���ڿ��� ����غ���
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, Response->GetContentAsString());

	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		bool Login = JsonObject->GetBoolField("Login");
		//FString result = Login ? TEXT("Login Success") : TEXT("Login Failed");
		PrintOnScreen(Login);
	}
}
=======
// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginObject.h"
#include "GameFramework/RootMotionSource.h"
#include "GameFramework/PlayerController.h"

ULoginObject::ULoginObject() {
	HttpModule = &FHttpModule::Get();
}

void ULoginObject::ExecuteLogin(FString id, FString password)
{
	/*TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule->CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	HttpRequest->SetURL("http://165.132.107.24:8000/accounts/login/");
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginObject::HttpRequestFinishedDelegate);
	HttpRequest->ProcessRequest();*/
}

void ULoginObject::HttpRequestFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSccessful) 
{
	if (bWasSccessful) {
		GLog->Log("Hey we received the following response!");
	}
	//�������κ��� ����� ������ ȭ�鿡 ����� ���ڿ��� ����غ���
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, Response->GetContentAsString());

	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		bool Login = JsonObject->GetBoolField("Login");
		//FString result = Login ? TEXT("Login Success") : TEXT("Login Failed");
		PrintOnScreen(Login);
	}
}
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
