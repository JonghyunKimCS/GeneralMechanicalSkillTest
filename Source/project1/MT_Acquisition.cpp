<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.


#include "MT_Acquisition.h"
#include "optimizer2.h"
#include <time.h>

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "UnrealClient.h"
#include "Components/InputComponent.h"


ofstream output_file3;
ifstream checker_file3;
string L2;

// Sets default values


AMT_Acquisition::AMT_Acquisition()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	num_trial = 40;
	big_num_trial = 9;
	num_correct = 0;
	num_correct_show = 0;
	trial = 0;
	target_speed = 2000.0f;
	target_width = 40.0f;
	FRandomStream Stream(FMath::Rand());
	interval = { 1.25f,1.8f,1.25f,1.8f,1.25f,1.8f,1.25f,1.8f };

	tcSet = {0.0f,0.0f,0.2f,0.2f,0.0f,0.0f,0.2f,0.2f };

	Wset = {0.080f,0.080f,0.080f,0.080f,0.150f,0.150f,0.150f,0.150f };

	conditions = {0,1,2,3,4,5,6,7};



	totalCorrect = 0;

	L2 = "";
	passed = false;
	clicked = false;
	need_create = true;
	bigTrial = 1;
	set = true;
	GameStarted = false;
	DataSended = false;
	stop = false;
	write = false;
	dist = tcSet[conditions[bigTrial - 1]] * target_speed;
	zone_width = Wset[conditions[bigTrial - 1]] * target_speed;
	zonemeet = false;
	zonex = 960 + 700 * 186 / 200;
	zoney = 540;
	targetx = 960 + (700.0f - zone_width / 2 - dist) * 186 / 200;
	targety = 540;
	oneTrigger = false;
	
}

// Called when the game starts or when spawned
void AMT_Acquisition::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;

	GameStarted = false;
	DataSended = false;
	Set2DView();
	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Sphere")) Lamp = Actor;
		if (Actor->GetName().Contains("Cube")) A_zone = Actor;
	}
	TimeTargetAppeard = GetWorld()->GetTimeSeconds();
	color_time = GetWorld()->GetTimeSeconds();
	TargetMeetZone = GetWorld()->GetTimeSeconds();


	A_zone->SetActorScale3D(FVector(zone_width / 100.0, zone_width / 100.0, 5.0f));

	Lamp->SetActorScale3D(FVector(target_width / 100.0f, target_width / 100.0f, target_width/100.0f));
	A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));
	UStaticMeshComponent* mesh = Lamp->FindComponentByClass<UStaticMeshComponent>();
	mesh->CreateDynamicMaterialInstance(0);
	mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0.0f, 1.0f, 0.0f));
	BindToInput();

	time_t seconds;
	seconds = time(NULL);
	srand(seconds);
	for (int32 k = 17; k > 0; k--) {
		int32 j = int(rand()) % conditions.Num();
		int temp = conditions[k % conditions.Num()];
		conditions[k % conditions.Num()] = conditions[j];
		conditions[j] = temp;
	}

	dist = tcSet[conditions[bigTrial - 1]] * target_speed;
	zone_width = Wset[conditions[bigTrial - 1]] * target_speed;


	string path;
	int i = 0;
	bool fileopen = false;

	while (!fileopen) {

		path = "../../../Log/MTA_" + to_string(i) + ".csv";

		checker_file3.open(path);
		if (!checker_file3.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file3.close();
	}

	output_file3.open(path, std::ios::out | std::ios::binary);
	output_file3 <<"UserID,Tc,Wa,P,Target-ZoneDistance,ZoneWidth,target_speed,target_width,t_zone,t_cue,targetX,TargetY,ZoneX,ZoneY,FrameRate,TimeTargetAppeard,TimeTargetMeetZone,ButtonPressed,TimeGap_Meet-Button,correct \n";
	
}

// Called every frame
void AMT_Acquisition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!write && bigTrial < (big_num_trial)) {
		FrameRate = 1.0f / DeltaTime;
		targetx = 960 + (700.0f - zone_width / 2 - dist) * 186 / 200;
		

		L2 = "";
		UE_LOG(LogTemp, Log, TEXT("write"));

		std::string userIDString(TCHAR_TO_UTF8(*userID));
		L2 = userIDString + "," + string_format("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", tcSet[conditions[bigTrial - 1]], Wset[conditions[bigTrial - 1]], interval[conditions[bigTrial - 1]], dist * 186 / 200, zone_width * 186 / 200, target_speed * 186 / 200, target_width * 186 / 200, zone_width / target_speed, dist / target_speed, targetx, targety, zonex, zoney, FrameRate);
		output_file3 << L2;
		write = true;
	}

	if (bigTrial == (big_num_trial) && GameStarted)
	{
		GameStarted = false;
		is_PressedE();
		output_file3.close();
		big_num_trial = 0;

	}


	if (trial == (num_trial + 1) && bigTrial != (big_num_trial - 1))
	{

		MTS::DATA d;
		d.p = float((interval[conditions[bigTrial - 1]]));
		d.t_zone = zone_width / target_speed;
		d.t_cue = dist / target_speed;
		d.y = 1.0f - float(num_correct) / float(trial - 6);
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), d.p, d.t_zone, d.t_cue, d.y);
		d.s = 0.0f;
		d.r = 0.0f;
		M.load_data(d);

		output_file3 << "\n";

		trial = 1;
		num_correct = 0;
		num_correct_show = 0;
		bigTrial++;
		L2 = "";

		dist = tcSet[conditions[bigTrial - 1]] * target_speed;
		zone_width = Wset[conditions[bigTrial - 1]] * target_speed;

		Lamp->SetActorLocation(FVector(2000, 700.0f - dist - zone_width / 2, 0.0f));
		A_zone->SetActorScale3D(FVector(zone_width / 100.0f, zone_width / 100.0f, 5.0f));
		write = false;
		stop = true;
	}

	if (trial == (num_trial + 1) && bigTrial == (big_num_trial - 1))
	{

		MTS::DATA d;
		d.p = float((interval[conditions[bigTrial - 1]]));
		d.t_zone = zone_width / target_speed;
		d.t_cue = dist / target_speed;
		d.y = 1.0f - float(num_correct) / float(trial - 6);
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), d.p, d.t_zone, d.t_cue, d.y);
		d.s = 0.0f;
		d.r = 0.0f;
		M.load_data(d);

		output_file3 << "\n";
		L2 = "";
		trial = 1;
		num_correct = 0;
		num_correct_show = 0;
		bigTrial++;
		write = false;
	}

	FVector Cur_location = Lamp->GetActorLocation();
	Lamp->SetActorLocation(Cur_location);
	if (Cur_location.Y >= 700 - zone_width / 2 && !zonemeet && Cur_location.Y < 700 + zone_width / 2) {
		///TargetMeetZone2 = TargetMeetZone;
		TargetMeetZone = GetWorld()->GetTimeSeconds();
		zonemeet = true;
	}

	if (stop) {
		TimeTargetAppeard = GetWorld()->GetTimeSeconds();
		BindToInput2();
		oneTrigger = true;
	}
	if (!stop && oneTrigger) {
		BindToInput();
		oneTrigger = false;
	}

	if (GameStarted && !stop) {
		Cur_location.Y += target_speed * DeltaTime;
		Lamp->SetActorLocation(Cur_location);
		if (Cur_location.Y > 700 + zone_width / 2) {
			passed = true;
			zonemeet = false;
		}
		else passed = false;


		time_now = GetWorld()->GetTimeSeconds();

		if (time_now - color_time > 0.3) {
			UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
			mesh->CreateDynamicMaterialInstance(0);
			mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 1.0f, 1.0f));
			A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));
		}

	}

	if (!DataSended && GameStarted && bigTrial != (big_num_trial) && !stop) { RepeatingFunc(); }
}


void AMT_Acquisition::GameStart()
{
	GameStarted = true;
}

void AMT_Acquisition::RepeatingFunc() //클릭하면 새로 생성
{
	
	if (need_create) {
		
		UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
		mesh->CreateDynamicMaterialInstance(0);
		mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 1.0f, 1.0f));
		A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));

		need_create = false;
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, FTimerDelegate::CreateLambda([&]() //delay time만큼의 delay 후 램프에 불 키기
			{	
				if (trial == (num_trial) && bigTrial != (big_num_trial - 1)) {
					//dist = tcSet[conditions[bigTrial]] * target_speed;				
				}

				Lamp->SetActorLocation(FVector(2000, 700.0f - dist - zone_width/2, 0.0f));
				
				need_create = true;
				if (trial != 0) {
										
					output_file3 << ',' + to_string(TimeTargetAppeard) + ',' + to_string(TargetMeetZone) + ',' + to_string(color_time) + ',' + to_string(color_time - TargetMeetZone) + ',' + to_string(writecorrect);
					//UE_LOG(LogTemp, Log, TEXT("%f,%f,%f,%f,%d"), TimeTargetAppeard, TargetMeetZone, color_time, color_time - TargetMeetZone, writecorrect);
					writecorrect = 0;
				}

				TimeTargetAppeard = GetWorld()->GetTimeSeconds();
				trial++;
			}), interval[conditions[bigTrial-1]], false);

	}
}
void AMT_Acquisition::BindToInput2() {
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();	
}



void AMT_Acquisition::BindToInput()
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &AMT_Acquisition::is_Pressed);
		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AMT_Acquisition::is_Pressed()
{		

	if (!stop) {
		if (Lamp->GetActorLocation().Y >= A_zone->GetActorLocation().Y - zone_width / 2 && Lamp->GetActorLocation().Y <= A_zone->GetActorLocation().Y + zone_width / 2)
		{
			UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
			mesh->CreateDynamicMaterialInstance(0);
			mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0.0f, 0.2f, 1.0f));
			A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));

			color_time = GetWorld()->GetTimeSeconds();

			writecorrect = 1;
			if (trial > 5) { num_correct++; }
			num_correct_show++;
			totalCorrect++;
		}
		else {

			UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
			mesh->CreateDynamicMaterialInstance(0);
			mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 0.0f, 0.0f));
			color_time = GetWorld()->GetTimeSeconds();

			writecorrect = 0;
			A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));

		}
		Lamp->SetActorLocation(FVector(1000, 1000, 1000));
	}
}

void AMT_Acquisition::is_PressedE() {

	string a = MOVING_TARGET_SELECTION::runOptimizer();


	a = a + ',' + to_string(1.0f - (float(totalCorrect) / 320.0f));
	ResultData = (a.c_str());
	UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData);

	DataSended = true;

	//return ResultString;
}

void AMT_Acquisition::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
}
=======
// Fill out your copyright notice in the Description page of Project Settings.


#include "MT_Acquisition.h"
#include "optimizer2.h"
#include <time.h>

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "UnrealClient.h"
#include "Components/InputComponent.h"


ofstream output_file3;
ifstream checker_file3;
string L2;

// Sets default values


AMT_Acquisition::AMT_Acquisition()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	num_trial = 40;
	big_num_trial = 9;
	num_correct = 0;
	num_correct_show = 0;
	trial = 0;
	target_speed = 2000.0f;
	target_width = 40.0f;
	FRandomStream Stream(FMath::Rand());
	interval = { 1.25f,1.8f,1.25f,1.8f,1.25f,1.8f,1.25f,1.8f };

	tcSet = {0.0f,0.0f,0.2f,0.2f,0.0f,0.0f,0.2f,0.2f };

	Wset = {0.080f,0.080f,0.080f,0.080f,0.150f,0.150f,0.150f,0.150f };

	conditions = {0,1,2,3,4,5,6,7};



	totalCorrect = 0;

	L2 = "";
	passed = false;
	clicked = false;
	need_create = true;
	bigTrial = 1;
	set = true;
	GameStarted = false;
	DataSended = false;
	stop = false;
	write = false;
	dist = tcSet[conditions[bigTrial - 1]] * target_speed;
	zone_width = Wset[conditions[bigTrial - 1]] * target_speed;
	zonemeet = false;
	zonex = 960 + 700 * 186 / 200;
	zoney = 540;
	targetx = 960 + (700.0f - zone_width / 2 - dist) * 186 / 200;
	targety = 540;
	oneTrigger = false;
	
}

// Called when the game starts or when spawned
void AMT_Acquisition::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;

	GameStarted = false;
	DataSended = false;
	Set2DView();
	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Sphere")) Lamp = Actor;
		if (Actor->GetName().Contains("Cube")) A_zone = Actor;
	}
	TimeTargetAppeard = GetWorld()->GetTimeSeconds();
	color_time = GetWorld()->GetTimeSeconds();
	TargetMeetZone = GetWorld()->GetTimeSeconds();


	A_zone->SetActorScale3D(FVector(zone_width / 100.0, zone_width / 100.0, 5.0f));

	Lamp->SetActorScale3D(FVector(target_width / 100.0f, target_width / 100.0f, target_width/100.0f));
	A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));
	UStaticMeshComponent* mesh = Lamp->FindComponentByClass<UStaticMeshComponent>();
	mesh->CreateDynamicMaterialInstance(0);
	mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0.0f, 1.0f, 0.0f));
	BindToInput();

	time_t seconds;
	seconds = time(NULL);
	srand(seconds);
	for (int32 k = 17; k > 0; k--) {
		int32 j = int(rand()) % conditions.Num();
		int temp = conditions[k % conditions.Num()];
		conditions[k % conditions.Num()] = conditions[j];
		conditions[j] = temp;
	}

	dist = tcSet[conditions[bigTrial - 1]] * target_speed;
	zone_width = Wset[conditions[bigTrial - 1]] * target_speed;


	string path;
	int i = 0;
	bool fileopen = false;

	while (!fileopen) {

		path = "../../../Log/MTA_" + to_string(i) + ".csv";

		checker_file3.open(path);
		if (!checker_file3.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file3.close();
	}

	output_file3.open(path, std::ios::out | std::ios::binary);
	output_file3 <<"UserID,Tc,Wa,P,Target-ZoneDistance,ZoneWidth,target_speed,target_width,t_zone,t_cue,targetX,TargetY,ZoneX,ZoneY,FrameRate,TimeTargetAppeard,TimeTargetMeetZone,ButtonPressed,TimeGap_Meet-Button,correct \n";
	
}

// Called every frame
void AMT_Acquisition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!write && bigTrial < (big_num_trial)) {
		FrameRate = 1.0f / DeltaTime;
		targetx = 960 + (700.0f - zone_width / 2 - dist) * 186 / 200;
		

		L2 = "";
		UE_LOG(LogTemp, Log, TEXT("write"));

		std::string userIDString(TCHAR_TO_UTF8(*userID));
		L2 = userIDString + "," + string_format("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", tcSet[conditions[bigTrial - 1]], Wset[conditions[bigTrial - 1]], interval[conditions[bigTrial - 1]], dist * 186 / 200, zone_width * 186 / 200, target_speed * 186 / 200, target_width * 186 / 200, zone_width / target_speed, dist / target_speed, targetx, targety, zonex, zoney, FrameRate);
		output_file3 << L2;
		write = true;
	}

	if (bigTrial == (big_num_trial) && GameStarted)
	{
		GameStarted = false;
		is_PressedE();
		output_file3.close();
		big_num_trial = 0;

	}


	if (trial == (num_trial + 1) && bigTrial != (big_num_trial - 1))
	{

		MTS::DATA d;
		d.p = float((interval[conditions[bigTrial - 1]]));
		d.t_zone = zone_width / target_speed;
		d.t_cue = dist / target_speed;
		d.y = 1.0f - float(num_correct) / float(trial - 6);
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), d.p, d.t_zone, d.t_cue, d.y);
		d.s = 0.0f;
		d.r = 0.0f;
		M.load_data(d);

		output_file3 << "\n";

		trial = 1;
		num_correct = 0;
		num_correct_show = 0;
		bigTrial++;
		L2 = "";

		dist = tcSet[conditions[bigTrial - 1]] * target_speed;
		zone_width = Wset[conditions[bigTrial - 1]] * target_speed;

		Lamp->SetActorLocation(FVector(2000, 700.0f - dist - zone_width / 2, 0.0f));
		A_zone->SetActorScale3D(FVector(zone_width / 100.0f, zone_width / 100.0f, 5.0f));
		write = false;
		stop = true;
	}

	if (trial == (num_trial + 1) && bigTrial == (big_num_trial - 1))
	{

		MTS::DATA d;
		d.p = float((interval[conditions[bigTrial - 1]]));
		d.t_zone = zone_width / target_speed;
		d.t_cue = dist / target_speed;
		d.y = 1.0f - float(num_correct) / float(trial - 6);
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), d.p, d.t_zone, d.t_cue, d.y);
		d.s = 0.0f;
		d.r = 0.0f;
		M.load_data(d);

		output_file3 << "\n";
		L2 = "";
		trial = 1;
		num_correct = 0;
		num_correct_show = 0;
		bigTrial++;
		write = false;
	}

	FVector Cur_location = Lamp->GetActorLocation();
	Lamp->SetActorLocation(Cur_location);
	if (Cur_location.Y >= 700 - zone_width / 2 && !zonemeet && Cur_location.Y < 700 + zone_width / 2) {
		///TargetMeetZone2 = TargetMeetZone;
		TargetMeetZone = GetWorld()->GetTimeSeconds();
		zonemeet = true;
	}

	if (stop) {
		TimeTargetAppeard = GetWorld()->GetTimeSeconds();
		BindToInput2();
		oneTrigger = true;
	}
	if (!stop && oneTrigger) {
		BindToInput();
		oneTrigger = false;
	}

	if (GameStarted && !stop) {
		Cur_location.Y += target_speed * DeltaTime;
		Lamp->SetActorLocation(Cur_location);
		if (Cur_location.Y > 700 + zone_width / 2) {
			passed = true;
			zonemeet = false;
		}
		else passed = false;


		time_now = GetWorld()->GetTimeSeconds();

		if (time_now - color_time > 0.3) {
			UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
			mesh->CreateDynamicMaterialInstance(0);
			mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 1.0f, 1.0f));
			A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));
		}

	}

	if (!DataSended && GameStarted && bigTrial != (big_num_trial) && !stop) { RepeatingFunc(); }
}


void AMT_Acquisition::GameStart()
{
	GameStarted = true;
}

void AMT_Acquisition::RepeatingFunc() //클릭하면 새로 생성
{
	
	if (need_create) {
		
		UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
		mesh->CreateDynamicMaterialInstance(0);
		mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 1.0f, 1.0f));
		A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));

		need_create = false;
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, FTimerDelegate::CreateLambda([&]() //delay time만큼의 delay 후 램프에 불 키기
			{	
				if (trial == (num_trial) && bigTrial != (big_num_trial - 1)) {
					//dist = tcSet[conditions[bigTrial]] * target_speed;				
				}

				Lamp->SetActorLocation(FVector(2000, 700.0f - dist - zone_width/2, 0.0f));
				
				need_create = true;
				if (trial != 0) {
										
					output_file3 << ',' + to_string(TimeTargetAppeard) + ',' + to_string(TargetMeetZone) + ',' + to_string(color_time) + ',' + to_string(color_time - TargetMeetZone) + ',' + to_string(writecorrect);
					//UE_LOG(LogTemp, Log, TEXT("%f,%f,%f,%f,%d"), TimeTargetAppeard, TargetMeetZone, color_time, color_time - TargetMeetZone, writecorrect);
					writecorrect = 0;
				}

				TimeTargetAppeard = GetWorld()->GetTimeSeconds();
				trial++;
			}), interval[conditions[bigTrial-1]], false);

	}
}
void AMT_Acquisition::BindToInput2() {
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();	
}



void AMT_Acquisition::BindToInput()
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &AMT_Acquisition::is_Pressed);
		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AMT_Acquisition::is_Pressed()
{		

	if (!stop) {
		if (Lamp->GetActorLocation().Y >= A_zone->GetActorLocation().Y - zone_width / 2 && Lamp->GetActorLocation().Y <= A_zone->GetActorLocation().Y + zone_width / 2)
		{
			UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
			mesh->CreateDynamicMaterialInstance(0);
			mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0.0f, 0.2f, 1.0f));
			A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));

			color_time = GetWorld()->GetTimeSeconds();

			writecorrect = 1;
			if (trial > 5) { num_correct++; }
			num_correct_show++;
			totalCorrect++;
		}
		else {

			UStaticMeshComponent* mesh = A_zone->FindComponentByClass<UStaticMeshComponent>();
			mesh->CreateDynamicMaterialInstance(0);
			mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 0.0f, 0.0f));
			color_time = GetWorld()->GetTimeSeconds();

			writecorrect = 0;
			A_zone->SetActorLocation(FVector(3000, 700.0f, 0.0f));

		}
		Lamp->SetActorLocation(FVector(1000, 1000, 1000));
	}
}

void AMT_Acquisition::is_PressedE() {

	string a = MOVING_TARGET_SELECTION::runOptimizer();


	a = a + ',' + to_string(1.0f - (float(totalCorrect) / 320.0f));
	ResultData = (a.c_str());
	UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData);

	DataSended = true;

	//return ResultString;
}

void AMT_Acquisition::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
}
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
