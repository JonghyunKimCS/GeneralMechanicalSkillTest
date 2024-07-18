<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<iostream>
#include "../../ThirdParty/pointing/pointing.h"
#define NOMINMAX
#include <windows.h>
#include "persistence1d.hpp"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MT_PointActor.generated.h"


UCLASS()
class PROJECT1_API AMT_PointActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMT_PointActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* Lamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool datasended;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //시행 횟수 iterator


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_success;
	int num_trial; //초기 시행횟수
	int next_click;
	float end_time; //버튼 누를때의 시각
	float start_time;//램프에 불이 켜질떄의 시각
	float target_speed;
	float target_width;
	float target_y;
	float target_z;
	float speed_y;
	float speed_z;
	bool clicked;
	bool collided_y;
	bool collided_z;
	bool start_game;
	bool isCorrect;
	int deltacount;
	int num_big_trial;
	float MX1;
	float MY1;
	float framecounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int big_trial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool startButtonPop;

	float timenow;
	float reactionTime;
	bool realStart;
	bool flag;
	bool positive;
	float before;
	float mouse_speed_compare;
	float tct_mouse_movement;
	float mouse_movement_length;
	int Stoic;
	

	pointing::PointingDevice* input;
	pointing::DisplayDevice* output;

	std::vector< float > speed;
	std::vector< float > speed_compare;
	std::vector< float > speed_smooth;

	std::vector< float > speed_raw;
	std::vector< float > speed_normalize;
	std::vector<int> min;
	std::vector<int> min2;
	std::vector<int> min3;
	std::vector<int> min4;
	std::vector<int> min5;
	std::vector<int> min6;


	float mouse_X;
	float mouse_Y;
	float reactionTime2;

	float cur_mouse_X;
	float cur_mouse_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_all;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float mouse_speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float Sfi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float fi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float tct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float er;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_4;
	
	FVector2D mouse_speed_vector;

	FVector2D ViewportSize;
	TArray<int> lamps;
	TArray<int> interval;
	TArray<float> scale;
	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RepeatingFunc();
	void BindToInput(); //키 이벤트 설정
	void MoveToMouseCursor(); // X
	void LoggingStart();
	void Set2DView(); //카메라 2d로 설정

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void GetTime();
};


//-------------------------------------------------------------------------------------------------------------------------------------
class MouseLoggingTask2:public FNonAbandonableTask
{
public:
	MouseLoggingTask2();
	~MouseLoggingTask2();

	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];
	MSG msg;


	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MouseLoggingTask2, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork();

};
=======
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<iostream>
#include "../../ThirdParty/pointing/pointing.h"
#define NOMINMAX
#include <windows.h>
#include "persistence1d.hpp"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MT_PointActor.generated.h"


UCLASS()
class PROJECT1_API AMT_PointActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMT_PointActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* Lamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool datasended;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //시행 횟수 iterator


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_success;
	int num_trial; //초기 시행횟수
	int next_click;
	float end_time; //버튼 누를때의 시각
	float start_time;//램프에 불이 켜질떄의 시각
	float target_speed;
	float target_width;
	float target_y;
	float target_z;
	float speed_y;
	float speed_z;
	bool clicked;
	bool collided_y;
	bool collided_z;
	bool start_game;
	bool isCorrect;
	int deltacount;
	int num_big_trial;
	float MX1;
	float MY1;
	float framecounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int big_trial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool startButtonPop;

	float timenow;
	float reactionTime;
	bool realStart;
	bool flag;
	bool positive;
	float before;
	float mouse_speed_compare;
	float tct_mouse_movement;
	float mouse_movement_length;
	int Stoic;
	

	pointing::PointingDevice* input;
	pointing::DisplayDevice* output;

	std::vector< float > speed;
	std::vector< float > speed_compare;
	std::vector< float > speed_smooth;

	std::vector< float > speed_raw;
	std::vector< float > speed_normalize;
	std::vector<int> min;
	std::vector<int> min2;
	std::vector<int> min3;
	std::vector<int> min4;
	std::vector<int> min5;
	std::vector<int> min6;


	float mouse_X;
	float mouse_Y;
	float reactionTime2;

	float cur_mouse_X;
	float cur_mouse_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_all;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float mouse_speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float ns6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float Sfi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float fi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float tct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float er;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float speed_compare_4;
	
	FVector2D mouse_speed_vector;

	FVector2D ViewportSize;
	TArray<int> lamps;
	TArray<int> interval;
	TArray<float> scale;
	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RepeatingFunc();
	void BindToInput(); //키 이벤트 설정
	void MoveToMouseCursor(); // X
	void LoggingStart();
	void Set2DView(); //카메라 2d로 설정

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void GetTime();
};


//-------------------------------------------------------------------------------------------------------------------------------------
class MouseLoggingTask2:public FNonAbandonableTask
{
public:
	MouseLoggingTask2();
	~MouseLoggingTask2();

	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];
	MSG msg;


	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MouseLoggingTask2, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork();

};
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
