<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "LoginObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpDownloadStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHttpDownloadProcessDelegate, int32, RecvSize, int32, TotalSize, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHttpDownloadFinishedDelegate, bool, bIsSuccess, FString, ContentPath);
/**
 * 
 */
UCLASS()
class PROJECT1_API ULoginObject : public UObject
{
	GENERATED_BODY()
public:
	ULoginObject();

	UFUNCTION(BlueprintCallable, DisplayName = "ExecuteLogin", Category = "LoginObject")
		void ExecuteLogin(FString id, FString password);

	UFUNCTION(BlueprintImplementableEvent, Category = "LoginObject")
		void PrintOnScreen(bool bLogin); // 정수 파라미터라면 int32형을 사용해야 한다

	UPROPERTY(BlueprintAssignable)
		FHttpDownloadStartDelegate OnDownloadStartCallback;

	UPROPERTY(BlueprintAssignable)
		FHttpDownloadProcessDelegate OnDownloadProcessCallback;

	UPROPERTY(BlueprintAssignable)
		FHttpDownloadFinishedDelegate OnDownloadFinishedCallback;

	APlayerController* SpecificPlayer1;

private:
	FHttpModule* HttpModule;

	void HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RecvBytes);

	void HttpRequestFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	// Ex: http://www.example.com/file.mp3
	UPROPERTY()
		FString SourceURL;

	// Ex: /Folder/Packs/
	UPROPERTY()
		FString Path;
	// Ex: MyVideo.mp4
	UPROPERTY()
		FString Name;
};
=======
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "LoginObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpDownloadStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHttpDownloadProcessDelegate, int32, RecvSize, int32, TotalSize, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHttpDownloadFinishedDelegate, bool, bIsSuccess, FString, ContentPath);
/**
 * 
 */
UCLASS()
class PROJECT1_API ULoginObject : public UObject
{
	GENERATED_BODY()
public:
	ULoginObject();

	UFUNCTION(BlueprintCallable, DisplayName = "ExecuteLogin", Category = "LoginObject")
		void ExecuteLogin(FString id, FString password);

	UFUNCTION(BlueprintImplementableEvent, Category = "LoginObject")
		void PrintOnScreen(bool bLogin); // 정수 파라미터라면 int32형을 사용해야 한다

	UPROPERTY(BlueprintAssignable)
		FHttpDownloadStartDelegate OnDownloadStartCallback;

	UPROPERTY(BlueprintAssignable)
		FHttpDownloadProcessDelegate OnDownloadProcessCallback;

	UPROPERTY(BlueprintAssignable)
		FHttpDownloadFinishedDelegate OnDownloadFinishedCallback;

	APlayerController* SpecificPlayer1;

private:
	FHttpModule* HttpModule;

	void HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RecvBytes);

	void HttpRequestFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	// Ex: http://www.example.com/file.mp3
	UPROPERTY()
		FString SourceURL;

	// Ex: /Folder/Packs/
	UPROPERTY()
		FString Path;
	// Ex: MyVideo.mp4
	UPROPERTY()
		FString Name;
};
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
