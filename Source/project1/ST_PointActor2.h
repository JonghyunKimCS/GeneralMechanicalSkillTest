<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define NOMINMAX
#include "../../ThirdParty/pointing/pointing.h"
#include "persistence1d.hpp"
#include <windows.h>
#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "ST_PointActor2.generated.h"


UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API AST_PointActor2 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AST_PointActor2();
	FTimerHandle CountdownTimerHandle1;
	FTimerHandle CountdownTimerHandle2;
	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;

	//virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) = 0;

	int cur_mouse_X;
	int cur_mouse_Y;
	int cur_mouse_X2;
	int cur_mouse_Y2;

	std::vector<float> kernel = { 0.05842299, 0.24210528, 0.39894347, 0.24210528, 0.05842299 };
	std::vector<float> speedset;

	float filtered_speed;

	float start_time;
	float end_time;

	float result_time2;
	float result_time1;

	int counter;

	/*
	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];	
	MSG msg;	
	*/

	//float dx;
	//float dy;
	



	/*
	pointing::PointingDevice* input;
	pointing::DisplayDevice* output;
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void QuitLogging();

	void LoggingStart();
	//void BindToInput();
	/*
	static void SetHook();
	static void UnHook();
		
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
	*/
};
//-------------------------------------------------------------------------------------------------------------------------------------
class MouseLoggingTask :public FNonAbandonableTask
{
public:
	MouseLoggingTask();
	~MouseLoggingTask();

	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];
	MSG msg;


	FORCEINLINE TStatId GetStatId() const
	{	
		RETURN_QUICK_DECLARE_CYCLE_STAT(MouseLoggingTask, STATGROUP_ThreadPoolAsyncTasks);	
	}

	void DoWork();

};
=======
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define NOMINMAX
#include "../../ThirdParty/pointing/pointing.h"
#include "persistence1d.hpp"
#include <windows.h>
#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "ST_PointActor2.generated.h"


UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API AST_PointActor2 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AST_PointActor2();
	FTimerHandle CountdownTimerHandle1;
	FTimerHandle CountdownTimerHandle2;
	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;

	//virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) = 0;

	int cur_mouse_X;
	int cur_mouse_Y;
	int cur_mouse_X2;
	int cur_mouse_Y2;

	std::vector<float> kernel = { 0.05842299, 0.24210528, 0.39894347, 0.24210528, 0.05842299 };
	std::vector<float> speedset;

	float filtered_speed;

	float start_time;
	float end_time;

	float result_time2;
	float result_time1;

	int counter;

	/*
	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];	
	MSG msg;	
	*/

	//float dx;
	//float dy;
	



	/*
	pointing::PointingDevice* input;
	pointing::DisplayDevice* output;
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void QuitLogging();

	void LoggingStart();
	//void BindToInput();
	/*
	static void SetHook();
	static void UnHook();
		
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
	*/
};
//-------------------------------------------------------------------------------------------------------------------------------------
class MouseLoggingTask :public FNonAbandonableTask
{
public:
	MouseLoggingTask();
	~MouseLoggingTask();

	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];
	MSG msg;


	FORCEINLINE TStatId GetStatId() const
	{	
		RETURN_QUICK_DECLARE_CYCLE_STAT(MouseLoggingTask, STATGROUP_ThreadPoolAsyncTasks);	
	}

	void DoWork();

};
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
