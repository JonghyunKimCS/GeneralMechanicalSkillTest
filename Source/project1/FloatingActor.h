<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include<vector>

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "FloatingActor.generated.h"


UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();
	virtual void RepeatingFunc();

	//UBlueprintGeneratedClass* LoadBP = LoadObject<UBlueprintGeneratedClass>(GetWorld(), TEXT("/Game/NewBlueprint.NewBlueprint_C"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	TArray<AActor*> Lamps; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	TArray<AActor*> Buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool DataSended = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool Epressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool GameStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //���� Ƚ�� iterator

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int Big_Trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool colored; //����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop; //����


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_Big_Trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_trial; //�ʱ� ����Ƚ��



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	bool file_opened;
	bool write_to_file;


	int writeCorrect;
	int writeColor;
	int num_pressed;
	int randint; //���� ���� index
	int interval; //���� ������ ����
	int num_lamp;
	float react_time;
	float delay_time;//random delay ��
	float end_time; //��ư �������� �ð�
	float start_time;//������ ���� �������� �ð�
	float total_react_time;
	bool pressed; //��ư 
	int isCorrect;
	bool need_change_color;
	bool Locate;
	int correctTotal;

	std::vector<int> Lit;
	std::vector<int> Press;
	std::vector<int> N;
	std::vector<float> RT;



	TArray<int> num_lamp_index;

	TArray<FKey> key_set; //����Ű�迭(1-2)
	FTimerHandle CountdownTimerHandle1;
	FTimerHandle CountdownTimerHandle2;
	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame	
	virtual void Tick(float DeltaTime) override;
	float delay(); //random delay ����
	void BindToInput(); //Ű �̺�Ʈ ����
	void is_Pressed1(); //����Ű1
	void is_Pressed2(); //����Ű2
	void is_Pressed3(); //����Ű3
	//void is_Pressed4(); //����Ű4

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void is_PressedE();

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void GameStart();
	void is_Pressed4(); //����Ű4
	void is_Pressed5();
	void is_Pressed6();
	void is_Pressed7();
	void is_Pressed8();
	void coloring(); //���� ��ĥ (�����)
	void Set2DView(); //ī�޶� 2d�� ����
	void LocateMaterial(int num_of_cube, TArray<AActor*> Lamps, TArray<AActor*> Buttons);

};
=======
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include<vector>

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "FloatingActor.generated.h"


UCLASS(Blueprintable, BlueprintType)
class PROJECT1_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();
	virtual void RepeatingFunc();

	//UBlueprintGeneratedClass* LoadBP = LoadObject<UBlueprintGeneratedClass>(GetWorld(), TEXT("/Game/NewBlueprint.NewBlueprint_C"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	TArray<AActor*> Lamps; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	TArray<AActor*> Buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	AActor* camera1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString ResultData2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool DataSended = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool Epressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool GameStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int trial; //���� Ƚ�� iterator

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int Big_Trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool colored; //����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	bool stop; //����


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_Big_Trial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	int num_trial; //�ʱ� ����Ƚ��



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables");
	FString userID;

	bool file_opened;
	bool write_to_file;


	int writeCorrect;
	int writeColor;
	int num_pressed;
	int randint; //���� ���� index
	int interval; //���� ������ ����
	int num_lamp;
	float react_time;
	float delay_time;//random delay ��
	float end_time; //��ư �������� �ð�
	float start_time;//������ ���� �������� �ð�
	float total_react_time;
	bool pressed; //��ư 
	int isCorrect;
	bool need_change_color;
	bool Locate;
	int correctTotal;

	std::vector<int> Lit;
	std::vector<int> Press;
	std::vector<int> N;
	std::vector<float> RT;



	TArray<int> num_lamp_index;

	TArray<FKey> key_set; //����Ű�迭(1-2)
	FTimerHandle CountdownTimerHandle1;
	FTimerHandle CountdownTimerHandle2;
	APlayerController* SpecificPlayer1;
	APlayerController* SpecificPlayer2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame	
	virtual void Tick(float DeltaTime) override;
	float delay(); //random delay ����
	void BindToInput(); //Ű �̺�Ʈ ����
	void is_Pressed1(); //����Ű1
	void is_Pressed2(); //����Ű2
	void is_Pressed3(); //����Ű3
	//void is_Pressed4(); //����Ű4

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void is_PressedE();

	UFUNCTION(BlueprintCallable, Category = "MyVariables")
	void GameStart();
	void is_Pressed4(); //����Ű4
	void is_Pressed5();
	void is_Pressed6();
	void is_Pressed7();
	void is_Pressed8();
	void coloring(); //���� ��ĥ (�����)
	void Set2DView(); //ī�޶� 2d�� ����
	void LocateMaterial(int num_of_cube, TArray<AActor*> Lamps, TArray<AActor*> Buttons);

};
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
