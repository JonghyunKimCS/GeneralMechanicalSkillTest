<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "persistence1d.hpp"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MT_Acquisition.generated.h"

UCLASS()
class PROJECT1_API AMT_Acquisition : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMT_Acquisition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* Lamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* A_zone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool DataSended = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool GameStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //시행 횟수 iterator

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_correct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_correct_show;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int big_num_trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	int next_click;
	float end_time; //버튼 누를때의 시각
	float start_time;//램프에 불이 켜질떄의 시각
	float target_speed;
	float target_width;
	float zone_width;
	float dist;
	float color_time;
	float time_now;
	float FrameRate;
	float TimeTargetAppeard;

	float TargetMeetZone;
	float TargetMeetZone2;

	float zonex;
	float zoney;
	float targetx;
	float targety;
	int totalCorrect;


	bool zonemeet;
	bool write;
	TArray<float> interval;
	TArray<float> tcSet;
	TArray<float> Wset;
	TArray<int> conditions;
	int writecorrect;
	bool clicked;
	bool passed;
	bool isCorrect;
	bool need_create;
	bool set;
	bool oneTrigger;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int bigTrial;

	FVector2D ViewportSize;
	FTimerHandle CountdownTimerHandle;
	APlayerController* SpecificPlayer1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RepeatingFunc();
	void BindToInput(); //키 이벤트 설정
	void is_Pressed();
	void Set2DView(); //카메라 2d로 설정
	void BindToInput2();
	UFUNCTION(BlueprintCallable, Category = "MyVariables")
		void is_PressedE();

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
		void GameStart();

};
=======
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "persistence1d.hpp"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MT_Acquisition.generated.h"

UCLASS()
class PROJECT1_API AMT_Acquisition : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMT_Acquisition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* Lamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* A_zone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool DataSended = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool GameStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //시행 횟수 iterator

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_correct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_correct_show;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int big_num_trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	int next_click;
	float end_time; //버튼 누를때의 시각
	float start_time;//램프에 불이 켜질떄의 시각
	float target_speed;
	float target_width;
	float zone_width;
	float dist;
	float color_time;
	float time_now;
	float FrameRate;
	float TimeTargetAppeard;

	float TargetMeetZone;
	float TargetMeetZone2;

	float zonex;
	float zoney;
	float targetx;
	float targety;
	int totalCorrect;


	bool zonemeet;
	bool write;
	TArray<float> interval;
	TArray<float> tcSet;
	TArray<float> Wset;
	TArray<int> conditions;
	int writecorrect;
	bool clicked;
	bool passed;
	bool isCorrect;
	bool need_create;
	bool set;
	bool oneTrigger;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int bigTrial;

	FVector2D ViewportSize;
	FTimerHandle CountdownTimerHandle;
	APlayerController* SpecificPlayer1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RepeatingFunc();
	void BindToInput(); //키 이벤트 설정
	void is_Pressed();
	void Set2DView(); //카메라 2d로 설정
	void BindToInput2();
	UFUNCTION(BlueprintCallable, Category = "MyVariables")
		void is_PressedE();

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
		void GameStart();

};
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
