<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define NOMINMAX
#include<iostream>
#include <windows.h>
#include "persistence1d.hpp"
#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "ST_PointActor.generated.h"


UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API AST_PointActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AST_PointActor();

	//UBlueprintGeneratedClass* LoadBP = LoadObject<UBlueprintGeneratedClass>(GetWorld(), TEXT("/Game/NewBlueprint.NewBlueprint_C"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	TArray<AActor*> Lamps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_show_trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_show_bigtrial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool startButtonPop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int BigTrial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //���� Ƚ�� iterator

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float frame; //���� Ƚ�� iterator


	int num_trial; //�ʱ� ����Ƚ��
	int num_lamp;
	int num_lamp_index;
	int next_click;
	float end_time; //��ư �������� �ð�
	float start_time;//������ ���� �������� �ð�
	bool start_game;
	bool isCorrect;
	bool clicked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool calculate;

	float speed_compare_1;
	float speed_compare_2;
	float speed_compare_3;
	float speed_compare_4;

	float redx;
	float redy;
	float bluex;
	float bluey;
	float ballsize;
	float writeDistance;
	float writeID;
	bool calculate1;
	float write_resultTime;
	int write_hit;
	bool set;
	int index_scale;
	int index_Distance;
	TArray<int> lamps;
	TArray<float> tilt;
	int intervalY1;
	int intervalY2;
	int intervalZ1;
	int intervalZ2;
	float resultTime;
	float resultTimeWrong;
	float MX;
	float MY;
	float MX1;
	float MY1;
	float MDX;
	float MDY;
	bool blue_click;
	int big_block;
	float mouse_speed_compare;
	float speed_compare_all;
	float timenow;
	float reactionTime;
	bool realStart;
	bool flag;
	bool positive;
	float before;
	int Stoic;
	int num_success;
	int num_ER;
	int num_ER_total;

	float mouse_X;
	float mouse_Y;
	float tct_mouse_movement;

	float mouse_speed;
	std::vector< float > speed;
	std::vector< float > speed_normalize;
	std::vector< float > speed_raw;
	std::vector< float > speed_smooth;
	std::vector< float > speed_compare;

	std::vector<int> min;
	std::vector<int> min2;
	std::vector<int> min3;
	std::vector<int> min4;
	std::vector<int> min5;
	std::vector<int> min6;


	std::vector<float> ID;
	std::vector<float> TCT;
	std::vector<float> TCTW;
	std::vector<float> ER;
	std::vector< float > W;
	std::vector< float > D;

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
	float fi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float Sfi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float er;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trials; //���� Ƚ�� iterator
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int blocks; //���� Ƚ�� iterator


	TArray<float> distance;
	TArray<float> scale;
	TArray<float> angle;
	TArray<int> combination;

	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void BindToInput(); //Ű �̺�Ʈ ����
	void is_Clicked(int); //lamp Ŭ����
	void MoveToMouseCursor(); // X
	void LoggingStart();
	void Set2DView(); //ī�޶� 2d�� ����

};


//-------------------------------------------------------------------------------------------------------------------------------------
class MouseLoggingTask1 :public FNonAbandonableTask
{
public:
	MouseLoggingTask1();
	~MouseLoggingTask1();

	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];
	MSG msg;


	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MouseLoggingTask1, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork();

};
=======
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define NOMINMAX
#include<iostream>
#include <windows.h>
#include "persistence1d.hpp"
#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "ST_PointActor.generated.h"


UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API AST_PointActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AST_PointActor();

	//UBlueprintGeneratedClass* LoadBP = LoadObject<UBlueprintGeneratedClass>(GetWorld(), TEXT("/Game/NewBlueprint.NewBlueprint_C"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	TArray<AActor*> Lamps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_show_trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_show_bigtrial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool startButtonPop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int BigTrial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //���� Ƚ�� iterator

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float frame; //���� Ƚ�� iterator


	int num_trial; //�ʱ� ����Ƚ��
	int num_lamp;
	int num_lamp_index;
	int next_click;
	float end_time; //��ư �������� �ð�
	float start_time;//������ ���� �������� �ð�
	bool start_game;
	bool isCorrect;
	bool clicked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool calculate;

	float speed_compare_1;
	float speed_compare_2;
	float speed_compare_3;
	float speed_compare_4;

	float redx;
	float redy;
	float bluex;
	float bluey;
	float ballsize;
	float writeDistance;
	float writeID;
	bool calculate1;
	float write_resultTime;
	int write_hit;
	bool set;
	int index_scale;
	int index_Distance;
	TArray<int> lamps;
	TArray<float> tilt;
	int intervalY1;
	int intervalY2;
	int intervalZ1;
	int intervalZ2;
	float resultTime;
	float resultTimeWrong;
	float MX;
	float MY;
	float MX1;
	float MY1;
	float MDX;
	float MDY;
	bool blue_click;
	int big_block;
	float mouse_speed_compare;
	float speed_compare_all;
	float timenow;
	float reactionTime;
	bool realStart;
	bool flag;
	bool positive;
	float before;
	int Stoic;
	int num_success;
	int num_ER;
	int num_ER_total;

	float mouse_X;
	float mouse_Y;
	float tct_mouse_movement;

	float mouse_speed;
	std::vector< float > speed;
	std::vector< float > speed_normalize;
	std::vector< float > speed_raw;
	std::vector< float > speed_smooth;
	std::vector< float > speed_compare;

	std::vector<int> min;
	std::vector<int> min2;
	std::vector<int> min3;
	std::vector<int> min4;
	std::vector<int> min5;
	std::vector<int> min6;


	std::vector<float> ID;
	std::vector<float> TCT;
	std::vector<float> TCTW;
	std::vector<float> ER;
	std::vector< float > W;
	std::vector< float > D;

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
	float fi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float Sfi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	float er;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trials; //���� Ƚ�� iterator
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int blocks; //���� Ƚ�� iterator


	TArray<float> distance;
	TArray<float> scale;
	TArray<float> angle;
	TArray<int> combination;

	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void BindToInput(); //Ű �̺�Ʈ ����
	void is_Clicked(int); //lamp Ŭ����
	void MoveToMouseCursor(); // X
	void LoggingStart();
	void Set2DView(); //ī�޶� 2d�� ����

};


//-------------------------------------------------------------------------------------------------------------------------------------
class MouseLoggingTask1 :public FNonAbandonableTask
{
public:
	MouseLoggingTask1();
	~MouseLoggingTask1();

	WNDCLASSEX wx;
	HWND hWnd;
	RAWINPUTDEVICE Rid[2];
	MSG msg;


	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MouseLoggingTask1, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork();

};
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
