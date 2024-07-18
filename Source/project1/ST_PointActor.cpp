<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#include "ST_PointActor.h"

#include "persistence1d.hpp"

extern "C" {
#include "hidsdi.h"
#include "SetupAPI.h"
}
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h>
#include <algorithm>
#include "../../ThirdParty/pointing/pointing.h"

#include "optimizer1.h"
#include <time.h>

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"

using namespace p1d;



ofstream output_file2;
ifstream checker_file2;



float dx1 = 0;
float dy1 = 0;
float buttonFlag1 = 0;
bool boolFlag1 = false;
bool GameOn1 = true;


// Sets default values



AST_PointActor::AST_PointActor()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	
	PrimaryActorTick.bCanEverTick = true;
	frame = 0;
	trials = 1;
	blocks = 1;
	num_lamp = 2;
	num_trial = 16;

	big_block = 3 ;
	num_show_trial = 96;
	num_show_bigtrial = 2;
	trial = 0;
	BigTrial = 1;
	calculate = false;
	calculate1 = false;
	start_game = false;
	set = false;
	next_click= 0;
	resultTime = 0;
	resultTimeWrong = 0;
	const float pi = 3.14 /8;
	stop = false;
	blue_click = false;
	tct_mouse_movement = 0;
	scale = { 0.09f, 0.22f , 0.30f };
	GameOn1 = true;

	distance = {120, 240};
	MX = 0;
	MY = 0;
	ns = 0;
	ns2 = 0;
	ns3 = 0;
	ns4 = 0;
	ns5 = 0;
	ns6 = 0;
	num_ER_total = 0;
	fi = 0;
	Sfi = 0;
	num_success = 0;
	num_ER = 0;
	angle = {pi*0 , pi * 15, pi * 14, pi * 13, pi * 12, pi * 11, pi * 10, pi * 9, pi * 8, pi * 7, pi * 6, pi * 5, pi * 4, pi * 3, pi * 2, pi * 1 };
	tilt = { 100, sin(angle[1]) / cos(angle[1]),sin(angle[2]) / cos(angle[2]) ,sin(angle[3]) / cos(angle[3]) ,0 ,sin(angle[5]) / cos(angle[5]) ,sin(angle[6]) / cos(angle[6]) ,sin(angle[7]) / cos(angle[7]) ,100,sin(angle[9]) / cos(angle[9]) ,sin(angle[10]) / cos(angle[10]) ,sin(angle[11]) / cos(angle[11]),0,sin(angle[13]) / cos(angle[13]),sin(angle[14]) / cos(angle[14]),sin(angle[15]) / cos(angle[15]) };	
	FRandomStream Stream(FMath::Rand());
	combination = { 0,1,2,3,4,5 };
	speed_compare_1 = 0;
	speed_compare_2 = 0;
	speed_compare_3 = 0;
	speed_compare_4 = 0;
	
}

// Called when the game starts or when spawned
void AST_PointActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	Set2DView();
		
	GameOn1 = true;

	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Sphere")) Lamps.Add(Actor);
	}

	UStaticMeshComponent* mesh1 = Lamps[0]->FindComponentByClass<UStaticMeshComponent>();
	mesh1->CreateDynamicMaterialInstance(0);
	mesh1->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 0.0f, 0.0f));

	UStaticMeshComponent* mesh2 = Lamps[1]->FindComponentByClass<UStaticMeshComponent>();
	mesh2->CreateDynamicMaterialInstance(0);
	mesh2->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0.0f, 0.0f, 1.0f));

	time_t seconds;
	seconds = time(NULL);
	srand(seconds);
	for (int32 k = 11; k > 0; k--) {
		int32 j = int(rand()) % combination.Num();
		int temp = combination[k % combination.Num()];
		combination[k % combination.Num()] = combination[j];
		combination[j] = temp;
	}

	
	//for (int i = 0; i < num_lamp; i++) {
	//	Lamps[i]->SetActorScale3D(FVector(scale[0], scale[0], scale[0]));
	//} 
	//Lamps[0]->SetActorLocation(FVector(-3000, interval[0], 400));
	//Lamps[1]->SetActorLocation(FVector(-3000, -interval[0], 400));


	//BindToInput();//여기까지 액터 위치 및 갯수 설정


	string path;
	int i = 0;
	bool fileopen = false;

	while (!fileopen) {

		path = "../../../Log/STP_" + to_string(i) + ".csv";

		checker_file2.open(path);
		if (!checker_file2.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file2.close();
	}
	speed_compare.push_back(1.0);
	output_file2.open(path, std::ios::out | std::ios::binary);
	//output_file2 << "UserID,Timestamp,Round,Trial,BallSize,Distance,ID, Red_X,Red_Y,BlueX,BlueY,MouseX,MouseY,MouseDX,MouseDY,NextClick,Click,Hit,ReactionTime,\n";
	output_file2 << "BallSize,Distance,Hit,ReactionTime,\n";

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MX, MY);

	LoggingStart();
	
	
}

// Called every frame
void AST_PointActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	
	//if (start_game) RepeatingFunc();
	//float cur_mouse_X;
	//float cur_mouse_Y;
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(cur_mouse_X, cur_mouse_Y);
	//UE_LOG(LogTemp, Log, TEXT("(%f, %f)"), cur_mouse_X, cur_mouse_Y);
	// = SpecificPlayer1->PlayerInput->GetBind('');
	//UE_LOG(LogTemp, Log, TEXT("%f"), MDX);
	
	if (boolFlag1 && !stop) { MoveToMouseCursor(); }
	else boolFlag1 = false;
	UE_LOG(LogTemp, Log, TEXT("(%f)"), 1 / DeltaTime);
	frame = 1.0f / DeltaTime;
	if (!clicked) {
		float time_now = GetWorld()->GetTimeSeconds();

		MX1 = MX;
		MY1 = MY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MX, MY);
		
			
		string L = "";
		writeDistance = distance[index_Distance] * 200.f / 120.f * 2.f;
		ballsize = scale[index_scale] * 200.f / 120.f * 100.f;
		writeID = log2((writeDistance / ballsize) + 1);
		redx = 960 + (distance[index_Distance] * 200.f / 120.f) * sin(angle[trial]);
		redy = 540 + (distance[index_Distance] * 200.f / 120.f) * cos(angle[trial]);
		bluex = 960 - (distance[index_Distance] * 200.f / 120.f) * sin(angle[trial]);
		bluey = 540 - (distance[index_Distance] * 200.f / 120.f) * cos(angle[trial]);
		ballsize = scale[index_scale] * 200.f / 120.f * 100.f;


		//바뀐부분
		//std::string userIDString(TCHAR_TO_UTF8(*userID));


		//바뀐부분
		//L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks, trials, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY,dx1,dy1, next_click, 0, 0, 0.0f) + '\n';
		//output_file2 << L;		


		mouse_speed = sqrt(dx1 * dx1 + dy1 * dy1) / (DeltaTime * 1000.f);
		
		if (sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1)) != 0) {
			mouse_speed_compare = sqrt(dx1 * dx1 + dy1 * dy1) / sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1));
		}
		//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);
		if (!stop) {						
			//UE_LOG(LogTemp, Log, TEXT("%f"), mouse_speed);
			if (mouse_speed_compare != speed_compare[speed_compare.size() - 1] && !((MX > 1910 && MX1 > 1910) || (MY1 > 1070 && MY > 1070) || (MY1 < 10 && MY < 10) || (MX < 10 && MX1 < 10))) { speed_compare.push_back(mouse_speed_compare); speed_raw.push_back(mouse_speed); /*UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);*/ }
			
			if (next_click == 1) { 
				speed.push_back(mouse_speed); 
				//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
				if (mouse_speed > 0) tct_mouse_movement += DeltaTime;
				//UE_LOG(LogTemp, Log, TEXT("(wa %f)"), tct_mouse_movement);
			}
		}
		
		dx1 = 0;
		dy1 = 0;
	}
	else {

		MX1 = MX;
		MY1 = MY;		
		float time_now = GetWorld()->GetTimeSeconds();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MX, MY);
		string L = "";

		//바뀐부분
		/*
		std::string userIDString(TCHAR_TO_UTF8(*userID));
		
		if (trials == 0 && blue_click){
			
			L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks-1, 96, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY, dx1, dy1, next_click, 1, write_hit, write_resultTime) + '\n';
			blue_click = false;
		}
		else if(blue_click){
			
			L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks, trials-1, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY, dx1, dy1, next_click, 1, write_hit, write_resultTime) + '\n';
			blue_click = false;
		}
		else {
			
			L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks, trials, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY, dx1, dy1, next_click, 1, write_hit, 0.0f) + '\n';
		}
		*/

		mouse_speed = sqrt(dx1 * dx1 + dy1 * dy1) / (DeltaTime * 1000.f);
		if (sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1)) != 0 && mouse_speed != 0) {
			mouse_speed_compare = sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1)) / sqrt(dx1 * dx1 + dy1 * dy1);
		}
		//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
		if (!stop) { 			
			//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
			if (mouse_speed_compare != speed_compare[speed_compare.size() - 1] && !((MX > 1910 && MX1 > 1910) || (MY1 > 1070 && MY > 1070) || (MY1 < 10 && MY < 10) || (MX < 10 && MX1 < 10))) { speed_compare.push_back(mouse_speed_compare); speed_raw.push_back(mouse_speed); /*UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare); */}
			if (next_click == 1) { speed.push_back(mouse_speed); }
		}
		
		dx1 = 0;
		dy1 = 0;

		//바뀐부분
		//output_file2 << L;
			
		clicked = false;
	}


	if (trial < num_trial && BigTrial < 7 && !set)
	{
		if (combination[BigTrial - 1] == 0) {
			index_scale = 0;
			index_Distance = 0;		
		}
		else if (combination[BigTrial - 1] == 1) {
			index_scale = 1;
			index_Distance = 0;
		}
		else if (combination[BigTrial - 1] == 2) {
			index_scale = 2;
			index_Distance = 0;
		}
		else if (combination[BigTrial - 1] == 3) {
			index_scale = 0;
			index_Distance = 1;
		}
		else if (combination[BigTrial - 1] == 4) {
			index_scale = 1;
			index_Distance = 1;
		}
		else if (combination[BigTrial - 1] == 5) {
			index_scale = 2;
			index_Distance = 1;
		}
		set = true;
		
	}

	if (trial < num_trial && BigTrial <7 && set && next_click == 0 && !stop)
	{
		for (int i = 0; i < num_lamp; i++) { Lamps[i]->SetActorScale3D(FVector(scale[index_scale], scale[index_scale], scale[index_scale])); }
		Lamps[0]->SetActorLocation(FVector(-3000, distance[index_Distance] * sin(angle[trial]) *186.f / 200.f, distance[index_Distance] * 186.f / 200.f * cos(angle[trial])));
		Lamps[1]->SetActorLocation(FVector(-3000, -(distance[index_Distance] * 186.f / 200.f * sin(angle[trial])), -(distance[index_Distance] * 186.f / 200.f * cos(angle[trial]))));
		//BindToInput();		
	}
	


	if (trial < num_trial && BigTrial < 7 && set && next_click == 1 && !stop)
	{
		for (int i = 0; i < num_lamp; i++) { Lamps[i]->SetActorScale3D(FVector(scale[index_scale], scale[index_scale], scale[index_scale])); }
		Lamps[0]->SetActorLocation(FVector(-3000, 5000, 5000));
		Lamps[1]->SetActorLocation(FVector(-3000, -(distance[index_Distance] * 186.0f / 200.0f * sin(angle[trial])), -(distance[index_Distance] * 186.0f / 200.f * cos(angle[trial]))));
		//BindToInput();
	}

	if (trial == num_trial && BigTrial < 7 )
	{	

		float id_W = scale[index_scale] * 200.0f / 120.0f * 100.0f;
		float id_D = distance[index_Distance] * 200.0f / 120.0f * 2.0f;
		
		ID.push_back(log2((id_D / id_W) + 1));
		TCT.push_back(resultTime / float(num_trial));
		TCTW.push_back(resultTimeWrong / float(num_trial + num_ER));
		ER.push_back( (float(num_ER) / float(num_trial + num_ER)));
		D.push_back(distance[index_Distance] * 200.0f / 120.0f * 2.0f);
		UE_LOG(LogTemp, Log, TEXT("%f,%f"), log2((id_D / id_W) + 1), (float(num_ER) / float(num_trial + num_ER)));
		num_ER = 0;
		UE_LOG(LogTemp, Log, TEXT("%f"), resultTime / float(num_trial));
		
		BigTrial++;
		trial = 0;
		resultTime = 0;
		resultTimeWrong = 0;
		set = false;


		
	}

	if (blocks < big_block && BigTrial == 7 && !calculate1 && !stop)
	{
		trials = 0;
		blocks++;
		BigTrial = 1;
		stop = true;

		er += float(num_success) / float(num_show_trial + num_ER_total);
		num_success = 0;
		num_ER_total = 0;
		//end_time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Log, TEXT("time :: %f seconds"), end_time - start_time);

		
	}
	
	if (blocks == big_block && !calculate1)
	{
		Lamps[0]->SetActorLocation(FVector(-3000, 5000, 400));
		Lamps[1]->SetActorLocation(FVector(-3000, 5000, 400));

		float maximum = *max_element(speed.begin(), speed.end());
		float minimum = *min_element(speed.begin(), speed.end());

		for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) { speed_normalize.push_back((speed[speed_counter] - minimum) / (maximum - minimum)); }
		for (int speed_counter2 = 1; speed_counter2 < speed_normalize.size()-1; speed_counter2++) { speed_smooth.push_back(speed_normalize[speed_counter2 -1] * 0.27901 + speed_normalize[speed_counter2] * 0.44198 + speed_normalize[speed_counter2+1] * 0.27901); }

		Persistence1D p;
		p.RunPersistence(speed_normalize);

		Persistence1D p2;
		p2.RunPersistence(speed_normalize);

		Persistence1D p3;
		p3.RunPersistence(speed_normalize);
		
		Persistence1D p4;
		p4.RunPersistence(speed_normalize);

		Persistence1D p5;
		p5.RunPersistence(speed_normalize);

		Persistence1D p6;
		p6.RunPersistence(speed_normalize);


		vector< TPairedExtrema > Extrema;		
		p.GetPairedExtrema(Extrema, 0.03);

		vector< TPairedExtrema > Extrema2;
		p2.GetPairedExtrema(Extrema2, 0.07);

		vector< TPairedExtrema > Extrema3;
		p3.GetPairedExtrema(Extrema3, 0.1);
		
		vector< TPairedExtrema > Extrema4;
		p4.GetPairedExtrema(Extrema4, 0.2);

		vector< TPairedExtrema > Extrema5;
		p5.GetPairedExtrema(Extrema5, 0.4);

		vector< TPairedExtrema > Extrema6;
		p6.GetPairedExtrema(Extrema6, 0.6);

		for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min.push_back((*it).MinIndex);
		}


		for (vector< TPairedExtrema >::iterator it = Extrema2.begin(); it != Extrema2.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min2.push_back((*it).MinIndex);
		}

		for (vector< TPairedExtrema >::iterator it = Extrema3.begin(); it != Extrema3.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min3.push_back((*it).MinIndex);
		}

		for (vector< TPairedExtrema >::iterator it = Extrema4.begin(); it != Extrema4.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min4.push_back((*it).MinIndex);
		}


		for (vector< TPairedExtrema >::iterator it = Extrema5.begin(); it != Extrema5.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min5.push_back((*it).MinIndex);
		}

		for (vector< TPairedExtrema >::iterator it = Extrema6.begin(); it != Extrema6.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min6.push_back((*it).MinIndex);
		}

		//std::sort(min.begin(), min.end());

		//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
		//}
		//
		// number of submovement

		UE_LOG(LogTemp, Log, TEXT("%d"), min.size());
		UE_LOG(LogTemp, Log, TEXT("%d"), min2.size());
		UE_LOG(LogTemp, Log, TEXT("%d"), min3.size());

		ns += min.size();
		ns2 += min2.size();
		ns3 += min3.size();
		ns4 += min4.size();
		ns5 += min5.size();
		ns6 += min6.size();


		flag = true;
		Stoic = 0;
		positive = true;

		for (vector<float>::iterator it = speed.begin(); it != speed.end(); it++) {

			if (flag) {
				flag = false;
			}
			else {
				if (positive && ((*it) - before < 0)) { Stoic++; positive = false; }
				else if (!positive && ((*it) - before > 0)) { Stoic++; positive = true; }
			}
			before = *it;
		}
		fi += Stoic;

		flag = true;
		Stoic = 0;
		positive = true;

		for (vector<float>::iterator it = speed_smooth.begin(); it != speed_smooth.end(); it++) {

			if (flag) {
				flag = false;
			}
			else {
				if (positive && ((*it) - before < 0)) { Stoic++; positive = false; }
				else if (!positive && ((*it) - before > 0)) { Stoic++; positive = true; }
			}
			before = *it;
		}
		Sfi += Stoic;


		UE_LOG(LogTemp, Log, TEXT("%d"), Stoic);


		UE_LOG(LogTemp, Log, TEXT("%f,%f,%f"), ns, fi, er);

		//UKismetSystemLibrary::QuitGame(GetWorld(), SpecificPlayer1, EQuitPreference::Quit, true);

		for (int counterp = 0; counterp < 6 ; counterp++) {

			FT::DATA d;
			int TCTN = 1;
			float TCTX = TCT[counterp];


			for (int counterp2 = 0; counterp2 < ID.size(); counterp2++) {
				if (ID[counterp] == ID[counterp2] && counterp2 != counterp) {
					TCTX = TCTX + TCT[counterp2];
					TCTN++;
				}				
			}
			
			d.ID = ID[counterp];
			d.MT = TCTX / float(TCTN);
			F.load_data(d);		
		}
		
		string a = FITTS_LAW::runOptimizer();
		F.clear();

		for (int counterp = 0; counterp < 6; counterp++) {

			FT::DATA d;
			int TCTN = 1;
			float TCTX = TCTW[counterp];
			float ERX = ER[counterp];


			for (int counterp2 = 0; counterp2 < ID.size(); counterp2++) {
				if (ID[counterp] == ID[counterp2] && counterp2 != counterp) {
					ERX = ERX + ER[counterp2];
					TCTX = TCTX + TCTW[counterp2];
					TCTN++;
				}
			}
			UE_LOG(LogTemp, Log, TEXT("%d, %d, %f"), ID.size(),  TCTN , (1.0f - (ERX / float(TCTN))));
			d.ID = (1.0f - (ERX / float(TCTN))) * ID[counterp];
			d.MT = TCTX / float(TCTN);
			F.load_data(d);
		}

		string b = FITTS_LAW::runOptimizer();
		F.clear();

		for (int counterp = 0; counterp < 6; counterp++) {

			FT::DATA d;
			int TCTN = 1;
			float TCTX = TCTW[counterp];
			float sum = 0;
			float STD = 0;
			for (int counterp2 = 0; counterp2 < ID.size(); counterp2++) {
				if (ID[counterp] == ID[counterp2] && counterp2 != counterp) {					
					TCTX = TCTX + TCTW[counterp2];
					TCTN++;

					for (int counterp3 = counterp * 16; counterp3 < counterp * 16 + 16; counterp3++) {sum += W[counterp3];}
					for (int counterp4 = counterp2 * 16; counterp4 < counterp2 * 16 + 16; counterp4++) {sum += W[counterp4];}
					float avg = sum / 32.f;
					sum = 0;
					for (int counterp3 = counterp * 16; counterp3 < counterp * 16 + 16; counterp3++) { sum += pow(W[counterp3] - avg, 2); }
					for (int counterp4 = counterp2 * 16; counterp4 < counterp2 * 16 + 16; counterp4++) { sum += pow(W[counterp4] - avg, 2); }
					float variance = sum / 32.f;
					STD = sqrt(variance);
				}
			}
			d.ID = log2((D[counterp] / (STD * 4.133)) + 1);
			d.MT = TCTX / float(TCTN);
			F.load_data(d);
		}
		string c = FITTS_LAW::runOptimizer();

		speed_compare_all = 0;

		float max = *max_element(speed_raw.begin(), speed_raw.end());
		max = max / 4.0f;

		int counter_1 = 0;
		int counter_2 = 0;
		int counter_3 = 0;
		int counter_4 = 0;

		for (int counterp4 = 0; counterp4 < speed_compare.size(); counterp4++) {

			if (speed_raw[counterp4] > max * 3) {
				speed_compare_4 += speed_compare[counterp4];
				counter_4++;
			}
			else if (speed_raw[counterp4] > max * 2) {
				speed_compare_3 += speed_compare[counterp4];
				counter_3++;
			}
			else if (speed_raw[counterp4] > max * 1) {
				speed_compare_2 += speed_compare[counterp4];
				counter_2++;
			}
			else{
				speed_compare_1 += speed_compare[counterp4];
				counter_1++;
			}
		}
		speed_compare_4 = speed_compare_4 / float(counter_4);
		speed_compare_3 = speed_compare_3 / float(counter_3);
		speed_compare_2 = speed_compare_2 / float(counter_2);
		speed_compare_1 = speed_compare_1 / float(counter_1);

		a = a + ',' + b +','+ c ;

		er = 1 - (er / float(num_show_bigtrial));
		float tctTotal = 0;
		for (int conterc = 0; conterc < TCT.size(); conterc++) { tctTotal += TCT[conterc]; }
		ns = ns / tct_mouse_movement;
		ns2 = ns2 / tct_mouse_movement;
		ns3 = ns3 / tct_mouse_movement;
		ns4 = ns4 / tct_mouse_movement;
		ns5 = ns5 / tct_mouse_movement;
		ns6 = ns6 / tct_mouse_movement;
		fi = fi / tct_mouse_movement;
		Sfi = Sfi / tct_mouse_movement;

		tctTotal = tctTotal / float(TCT.size());
		a = a + string_format(",%f,%f,%f,%f", ns, fi, er, tctTotal);
		a = a + string_format(",%f,%f,%f,%f", speed_compare_4, speed_compare_3, speed_compare_2, speed_compare_1);
		ResultData = (a.c_str());
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), speed_compare_4, speed_compare_3, speed_compare_2, speed_compare_1);
		UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData);

		GameOn1 = false;
		output_file2.close();
		calculate1 = true;
		calculate = true;
	}
	

}

void AST_PointActor::BindToInput()
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("InputClick", IE_Pressed, this, &AST_PointActor::MoveToMouseCursor);
		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AST_PointActor::is_Clicked(int index)
{
	if (index == 0) {
		start_time = GetWorld()->GetTimeSeconds();
		next_click = 1;
		clicked = true;

	}
	else if (index == 3 && next_click == 1) {
		end_time = GetWorld()->GetTimeSeconds();
		resultTimeWrong += end_time - start_time;
		next_click = 0;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouse_X, mouse_Y);
		mouse_X = mouse_X - 960;
		mouse_Y = 540 - mouse_Y;
		float red_x = 960 - redx;
		float red_y = redy - 540 ;

		UE_LOG(LogTemp, Log, TEXT("%f,%f.%f.%f"), mouse_X, mouse_Y, red_x, red_y);


		if (tilt[trial] == 100) { W.push_back(abs(red_y - mouse_Y)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_y - mouse_Y)); }
		else if (tilt[trial] == 0) { W.push_back(abs(red_x - mouse_X)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_x - mouse_X)); }
		else {
			float a = red_y / red_x;
			UE_LOG(LogTemp, Log, TEXT("%f"), a);
			float c = (1 / a) * mouse_X + mouse_Y;
			float newx = c / (a + (1 / a));
			float newy = a * newx;
			W.push_back(sqrt((red_x - newx) * (red_x - newx) + (red_y - newy) * (red_y - newy)));
			UE_LOG(LogTemp, Log, TEXT("%f"), sqrt((red_x - newx) * (red_x - newx) + (red_y - newy) * (red_y - newy)));
		}
		clicked = true;
		
	}

	else {
		if (next_click == 1 && index == 1) {
			end_time = GetWorld()->GetTimeSeconds();
			write_resultTime = end_time - start_time;
			resultTimeWrong += end_time - start_time;
			resultTime += end_time - start_time;
			next_click = 0;
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouse_X, mouse_Y);
			mouse_X = mouse_X - 960;
			mouse_Y = 540 - mouse_Y;
			float red_x = 960 - redx;
			float red_y = redy - 540;

			UE_LOG(LogTemp, Log, TEXT("%f,%f.%f.%f"),mouse_X, mouse_Y, red_x, red_y);
	

			if (tilt[trial] == 100) { W.push_back(abs(red_y -mouse_Y)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_y - mouse_Y));	}
			else if (tilt[trial] == 0) { W.push_back(abs(red_x -mouse_X)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_x - mouse_X));}
			else {
				float a = red_y / red_x ;
				UE_LOG(LogTemp, Log, TEXT("%f"), a);
				float c = (1 / a) * mouse_X + mouse_Y;
				float newx = c / (a + (1 / a));
				float newy = a * newx;
				W.push_back(sqrt((red_x - newx)*(red_x - newx) + (red_y - newy)*(red_y - newy)));
				UE_LOG(LogTemp, Log, TEXT("%f"), sqrt((red_x - newx) * (red_x - newx) + (red_y - newy) * (red_y - newy)));
			}

			clicked = true;
			trial++;
			trials++;
			blue_click = true;
			
		}

	}
		
}



void AST_PointActor::MoveToMouseCursor()
{
	boolFlag1 = false;
	FHitResult Hit;
	SpecificPlayer1->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	//UE_LOG(LogTemp, Log, TEXT("cluck"));
	if (Hit.bBlockingHit)
	{
		AActor* hitactor = Hit.GetActor();
		if (Lamps[0]->GetName() == hitactor->GetName()) {
			is_Clicked(0);
			write_hit = 1;
			
		}
		else if (Lamps[1]->GetName() == hitactor->GetName()) {
			is_Clicked(1);
			
			//바뀐부분
			string L;
			L = string_format("%f,%f,%d,%f", ballsize, writeDistance, 1, write_resultTime) + '\n';
			output_file2 << L;
			write_hit = 1;
			num_success++;			
		}		
	}
	else if (next_click == 0){		
		write_hit = 0;
		clicked = true;
	}
	else if(next_click == 1) {
		
		is_Clicked(3);
		string L;
		L = string_format("%f,%f,%d,%f", ballsize, writeDistance, 0, write_resultTime) + '\n';
		output_file2 << L;
		num_ER++;
		num_ER_total++;
		UE_LOG(LogTemp, Log, TEXT("work"));
		write_hit = 0;
	}
}

void AST_PointActor::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
}



void AST_PointActor::LoggingStart() {

	(new FAutoDeleteAsyncTask<MouseLoggingTask1>())->StartBackgroundTask();
}


//------------------------------------------------------------------------------


MouseLoggingTask1::MouseLoggingTask1() {
	UE_LOG(LogTemp, Log, TEXT("Start"));
}



MouseLoggingTask1::~MouseLoggingTask1() {
	UE_LOG(LogTemp, Log, TEXT("End"));
}


void MouseLoggingTask1::DoWork() {

	dx1 = 0;
	dy1 = 0;

	wx = {};
	wx.cbSize = sizeof(WNDCLASSEX);
	wx.lpfnWndProc = DefWindowProc;
	wx.hInstance = GetModuleHandle(NULL);
	wx.lpszClassName = TEXT("MyRawInputWndClass");

	if (!RegisterClassEx(&wx))
	{
		UE_LOG(LogTemp, Log, TEXT("failed 1"));
	}

	hWnd = CreateWindowEx(0, wx.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wx.hInstance, NULL);

	if (!hWnd)
	{
		UE_LOG(LogTemp, Log, TEXT("failed 2"));
	}

	Rid[0].usUsagePage = 0x01;
	Rid[0].usUsage = 0x02;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = hWnd;

	Rid[1].usUsagePage = 0x01;
	Rid[1].usUsage = 0x06;
	Rid[1].dwFlags = RIDEV_INPUTSINK;
	Rid[1].hwndTarget = hWnd;

	if (!RegisterRawInputDevices(Rid, 2, sizeof(RAWINPUTDEVICE)))
	{
		UE_LOG(LogTemp, Log, TEXT("failed 3"));
	}

	while (GameOn1) {

		GetMessage(&msg, NULL, 0, 0);
		//std::cout << "HERE" << std::endl;
		if (msg.message == WM_INPUT) {
			UINT dwSize = 0;
			GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
			LPBYTE lpb = new BYTE[dwSize];
			if (GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
				throw std::runtime_error("GetRawInputData does not return correct size !\n");
			RAWINPUT* raw = (RAWINPUT*)(lpb);
			//std::cout << raw->data.keyboard.Reserved << std::endl;
			if (raw->header.dwType == RIM_TYPEMOUSE) {
				dx1 += raw->data.mouse.lLastX;
				dy1 += raw->data.mouse.lLastY;
				buttonFlag1 = raw->data.mouse.usButtonFlags;
				if (buttonFlag1 == 1) { boolFlag1 = true; }
				//UE_LOG(LogTemp, Log, TEXT("%f"), dx1);
			}
			else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
			}
			HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
			// retrieve and process data from hRawInput as needed...
			//std::cout << msg.pt.x << std::endl;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
}


=======
// Fill out your copyright notice in the Description page of Project Settings.

#include "ST_PointActor.h"

#include "persistence1d.hpp"

extern "C" {
#include "hidsdi.h"
#include "SetupAPI.h"
}
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h>
#include <algorithm>
#include "../../ThirdParty/pointing/pointing.h"

#include "optimizer1.h"
#include <time.h>

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"

using namespace p1d;



ofstream output_file2;
ifstream checker_file2;



float dx1 = 0;
float dy1 = 0;
float buttonFlag1 = 0;
bool boolFlag1 = false;
bool GameOn1 = true;


// Sets default values



AST_PointActor::AST_PointActor()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	
	PrimaryActorTick.bCanEverTick = true;
	frame = 0;
	trials = 1;
	blocks = 1;
	num_lamp = 2;
	num_trial = 16;

	big_block = 3 ;
	num_show_trial = 96;
	num_show_bigtrial = 2;
	trial = 0;
	BigTrial = 1;
	calculate = false;
	calculate1 = false;
	start_game = false;
	set = false;
	next_click= 0;
	resultTime = 0;
	resultTimeWrong = 0;
	const float pi = 3.14 /8;
	stop = false;
	blue_click = false;
	tct_mouse_movement = 0;
	scale = { 0.09f, 0.22f , 0.30f };
	GameOn1 = true;

	distance = {120, 240};
	MX = 0;
	MY = 0;
	ns = 0;
	ns2 = 0;
	ns3 = 0;
	ns4 = 0;
	ns5 = 0;
	ns6 = 0;
	num_ER_total = 0;
	fi = 0;
	Sfi = 0;
	num_success = 0;
	num_ER = 0;
	angle = {pi*0 , pi * 15, pi * 14, pi * 13, pi * 12, pi * 11, pi * 10, pi * 9, pi * 8, pi * 7, pi * 6, pi * 5, pi * 4, pi * 3, pi * 2, pi * 1 };
	tilt = { 100, sin(angle[1]) / cos(angle[1]),sin(angle[2]) / cos(angle[2]) ,sin(angle[3]) / cos(angle[3]) ,0 ,sin(angle[5]) / cos(angle[5]) ,sin(angle[6]) / cos(angle[6]) ,sin(angle[7]) / cos(angle[7]) ,100,sin(angle[9]) / cos(angle[9]) ,sin(angle[10]) / cos(angle[10]) ,sin(angle[11]) / cos(angle[11]),0,sin(angle[13]) / cos(angle[13]),sin(angle[14]) / cos(angle[14]),sin(angle[15]) / cos(angle[15]) };	
	FRandomStream Stream(FMath::Rand());
	combination = { 0,1,2,3,4,5 };
	speed_compare_1 = 0;
	speed_compare_2 = 0;
	speed_compare_3 = 0;
	speed_compare_4 = 0;
	
}

// Called when the game starts or when spawned
void AST_PointActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	Set2DView();
		
	GameOn1 = true;

	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Sphere")) Lamps.Add(Actor);
	}

	UStaticMeshComponent* mesh1 = Lamps[0]->FindComponentByClass<UStaticMeshComponent>();
	mesh1->CreateDynamicMaterialInstance(0);
	mesh1->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 0.0f, 0.0f));

	UStaticMeshComponent* mesh2 = Lamps[1]->FindComponentByClass<UStaticMeshComponent>();
	mesh2->CreateDynamicMaterialInstance(0);
	mesh2->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0.0f, 0.0f, 1.0f));

	time_t seconds;
	seconds = time(NULL);
	srand(seconds);
	for (int32 k = 11; k > 0; k--) {
		int32 j = int(rand()) % combination.Num();
		int temp = combination[k % combination.Num()];
		combination[k % combination.Num()] = combination[j];
		combination[j] = temp;
	}

	
	//for (int i = 0; i < num_lamp; i++) {
	//	Lamps[i]->SetActorScale3D(FVector(scale[0], scale[0], scale[0]));
	//} 
	//Lamps[0]->SetActorLocation(FVector(-3000, interval[0], 400));
	//Lamps[1]->SetActorLocation(FVector(-3000, -interval[0], 400));


	//BindToInput();//여기까지 액터 위치 및 갯수 설정


	string path;
	int i = 0;
	bool fileopen = false;

	while (!fileopen) {

		path = "../../../Log/STP_" + to_string(i) + ".csv";

		checker_file2.open(path);
		if (!checker_file2.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file2.close();
	}
	speed_compare.push_back(1.0);
	output_file2.open(path, std::ios::out | std::ios::binary);
	//output_file2 << "UserID,Timestamp,Round,Trial,BallSize,Distance,ID, Red_X,Red_Y,BlueX,BlueY,MouseX,MouseY,MouseDX,MouseDY,NextClick,Click,Hit,ReactionTime,\n";
	output_file2 << "BallSize,Distance,Hit,ReactionTime,\n";

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MX, MY);

	LoggingStart();
	
	
}

// Called every frame
void AST_PointActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	
	//if (start_game) RepeatingFunc();
	//float cur_mouse_X;
	//float cur_mouse_Y;
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(cur_mouse_X, cur_mouse_Y);
	//UE_LOG(LogTemp, Log, TEXT("(%f, %f)"), cur_mouse_X, cur_mouse_Y);
	// = SpecificPlayer1->PlayerInput->GetBind('');
	//UE_LOG(LogTemp, Log, TEXT("%f"), MDX);
	
	if (boolFlag1 && !stop) { MoveToMouseCursor(); }
	else boolFlag1 = false;
	UE_LOG(LogTemp, Log, TEXT("(%f)"), 1 / DeltaTime);
	frame = 1.0f / DeltaTime;
	if (!clicked) {
		float time_now = GetWorld()->GetTimeSeconds();

		MX1 = MX;
		MY1 = MY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MX, MY);
		
			
		string L = "";
		writeDistance = distance[index_Distance] * 200.f / 120.f * 2.f;
		ballsize = scale[index_scale] * 200.f / 120.f * 100.f;
		writeID = log2((writeDistance / ballsize) + 1);
		redx = 960 + (distance[index_Distance] * 200.f / 120.f) * sin(angle[trial]);
		redy = 540 + (distance[index_Distance] * 200.f / 120.f) * cos(angle[trial]);
		bluex = 960 - (distance[index_Distance] * 200.f / 120.f) * sin(angle[trial]);
		bluey = 540 - (distance[index_Distance] * 200.f / 120.f) * cos(angle[trial]);
		ballsize = scale[index_scale] * 200.f / 120.f * 100.f;


		//바뀐부분
		//std::string userIDString(TCHAR_TO_UTF8(*userID));


		//바뀐부분
		//L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks, trials, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY,dx1,dy1, next_click, 0, 0, 0.0f) + '\n';
		//output_file2 << L;		


		mouse_speed = sqrt(dx1 * dx1 + dy1 * dy1) / (DeltaTime * 1000.f);
		
		if (sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1)) != 0) {
			mouse_speed_compare = sqrt(dx1 * dx1 + dy1 * dy1) / sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1));
		}
		//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);
		if (!stop) {						
			//UE_LOG(LogTemp, Log, TEXT("%f"), mouse_speed);
			if (mouse_speed_compare != speed_compare[speed_compare.size() - 1] && !((MX > 1910 && MX1 > 1910) || (MY1 > 1070 && MY > 1070) || (MY1 < 10 && MY < 10) || (MX < 10 && MX1 < 10))) { speed_compare.push_back(mouse_speed_compare); speed_raw.push_back(mouse_speed); /*UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);*/ }
			
			if (next_click == 1) { 
				speed.push_back(mouse_speed); 
				//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
				if (mouse_speed > 0) tct_mouse_movement += DeltaTime;
				//UE_LOG(LogTemp, Log, TEXT("(wa %f)"), tct_mouse_movement);
			}
		}
		
		dx1 = 0;
		dy1 = 0;
	}
	else {

		MX1 = MX;
		MY1 = MY;		
		float time_now = GetWorld()->GetTimeSeconds();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MX, MY);
		string L = "";

		//바뀐부분
		/*
		std::string userIDString(TCHAR_TO_UTF8(*userID));
		
		if (trials == 0 && blue_click){
			
			L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks-1, 96, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY, dx1, dy1, next_click, 1, write_hit, write_resultTime) + '\n';
			blue_click = false;
		}
		else if(blue_click){
			
			L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks, trials-1, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY, dx1, dy1, next_click, 1, write_hit, write_resultTime) + '\n';
			blue_click = false;
		}
		else {
			
			L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f", time_now, blocks, trials, ballsize, writeDistance, writeID, redx, redy, bluex, bluey, MX, MY, dx1, dy1, next_click, 1, write_hit, 0.0f) + '\n';
		}
		*/

		mouse_speed = sqrt(dx1 * dx1 + dy1 * dy1) / (DeltaTime * 1000.f);
		if (sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1)) != 0 && mouse_speed != 0) {
			mouse_speed_compare = sqrt((MX - MX1) * (MX - MX1) + (MY - MY1) * (MY - MY1)) / sqrt(dx1 * dx1 + dy1 * dy1);
		}
		//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
		if (!stop) { 			
			//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
			if (mouse_speed_compare != speed_compare[speed_compare.size() - 1] && !((MX > 1910 && MX1 > 1910) || (MY1 > 1070 && MY > 1070) || (MY1 < 10 && MY < 10) || (MX < 10 && MX1 < 10))) { speed_compare.push_back(mouse_speed_compare); speed_raw.push_back(mouse_speed); /*UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare); */}
			if (next_click == 1) { speed.push_back(mouse_speed); }
		}
		
		dx1 = 0;
		dy1 = 0;

		//바뀐부분
		//output_file2 << L;
			
		clicked = false;
	}


	if (trial < num_trial && BigTrial < 7 && !set)
	{
		if (combination[BigTrial - 1] == 0) {
			index_scale = 0;
			index_Distance = 0;		
		}
		else if (combination[BigTrial - 1] == 1) {
			index_scale = 1;
			index_Distance = 0;
		}
		else if (combination[BigTrial - 1] == 2) {
			index_scale = 2;
			index_Distance = 0;
		}
		else if (combination[BigTrial - 1] == 3) {
			index_scale = 0;
			index_Distance = 1;
		}
		else if (combination[BigTrial - 1] == 4) {
			index_scale = 1;
			index_Distance = 1;
		}
		else if (combination[BigTrial - 1] == 5) {
			index_scale = 2;
			index_Distance = 1;
		}
		set = true;
		
	}

	if (trial < num_trial && BigTrial <7 && set && next_click == 0 && !stop)
	{
		for (int i = 0; i < num_lamp; i++) { Lamps[i]->SetActorScale3D(FVector(scale[index_scale], scale[index_scale], scale[index_scale])); }
		Lamps[0]->SetActorLocation(FVector(-3000, distance[index_Distance] * sin(angle[trial]) *186.f / 200.f, distance[index_Distance] * 186.f / 200.f * cos(angle[trial])));
		Lamps[1]->SetActorLocation(FVector(-3000, -(distance[index_Distance] * 186.f / 200.f * sin(angle[trial])), -(distance[index_Distance] * 186.f / 200.f * cos(angle[trial]))));
		//BindToInput();		
	}
	


	if (trial < num_trial && BigTrial < 7 && set && next_click == 1 && !stop)
	{
		for (int i = 0; i < num_lamp; i++) { Lamps[i]->SetActorScale3D(FVector(scale[index_scale], scale[index_scale], scale[index_scale])); }
		Lamps[0]->SetActorLocation(FVector(-3000, 5000, 5000));
		Lamps[1]->SetActorLocation(FVector(-3000, -(distance[index_Distance] * 186.0f / 200.0f * sin(angle[trial])), -(distance[index_Distance] * 186.0f / 200.f * cos(angle[trial]))));
		//BindToInput();
	}

	if (trial == num_trial && BigTrial < 7 )
	{	

		float id_W = scale[index_scale] * 200.0f / 120.0f * 100.0f;
		float id_D = distance[index_Distance] * 200.0f / 120.0f * 2.0f;
		
		ID.push_back(log2((id_D / id_W) + 1));
		TCT.push_back(resultTime / float(num_trial));
		TCTW.push_back(resultTimeWrong / float(num_trial + num_ER));
		ER.push_back( (float(num_ER) / float(num_trial + num_ER)));
		D.push_back(distance[index_Distance] * 200.0f / 120.0f * 2.0f);
		UE_LOG(LogTemp, Log, TEXT("%f,%f"), log2((id_D / id_W) + 1), (float(num_ER) / float(num_trial + num_ER)));
		num_ER = 0;
		UE_LOG(LogTemp, Log, TEXT("%f"), resultTime / float(num_trial));
		
		BigTrial++;
		trial = 0;
		resultTime = 0;
		resultTimeWrong = 0;
		set = false;


		
	}

	if (blocks < big_block && BigTrial == 7 && !calculate1 && !stop)
	{
		trials = 0;
		blocks++;
		BigTrial = 1;
		stop = true;

		er += float(num_success) / float(num_show_trial + num_ER_total);
		num_success = 0;
		num_ER_total = 0;
		//end_time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Log, TEXT("time :: %f seconds"), end_time - start_time);

		
	}
	
	if (blocks == big_block && !calculate1)
	{
		Lamps[0]->SetActorLocation(FVector(-3000, 5000, 400));
		Lamps[1]->SetActorLocation(FVector(-3000, 5000, 400));

		float maximum = *max_element(speed.begin(), speed.end());
		float minimum = *min_element(speed.begin(), speed.end());

		for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) { speed_normalize.push_back((speed[speed_counter] - minimum) / (maximum - minimum)); }
		for (int speed_counter2 = 1; speed_counter2 < speed_normalize.size()-1; speed_counter2++) { speed_smooth.push_back(speed_normalize[speed_counter2 -1] * 0.27901 + speed_normalize[speed_counter2] * 0.44198 + speed_normalize[speed_counter2+1] * 0.27901); }

		Persistence1D p;
		p.RunPersistence(speed_normalize);

		Persistence1D p2;
		p2.RunPersistence(speed_normalize);

		Persistence1D p3;
		p3.RunPersistence(speed_normalize);
		
		Persistence1D p4;
		p4.RunPersistence(speed_normalize);

		Persistence1D p5;
		p5.RunPersistence(speed_normalize);

		Persistence1D p6;
		p6.RunPersistence(speed_normalize);


		vector< TPairedExtrema > Extrema;		
		p.GetPairedExtrema(Extrema, 0.03);

		vector< TPairedExtrema > Extrema2;
		p2.GetPairedExtrema(Extrema2, 0.07);

		vector< TPairedExtrema > Extrema3;
		p3.GetPairedExtrema(Extrema3, 0.1);
		
		vector< TPairedExtrema > Extrema4;
		p4.GetPairedExtrema(Extrema4, 0.2);

		vector< TPairedExtrema > Extrema5;
		p5.GetPairedExtrema(Extrema5, 0.4);

		vector< TPairedExtrema > Extrema6;
		p6.GetPairedExtrema(Extrema6, 0.6);

		for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min.push_back((*it).MinIndex);
		}


		for (vector< TPairedExtrema >::iterator it = Extrema2.begin(); it != Extrema2.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min2.push_back((*it).MinIndex);
		}

		for (vector< TPairedExtrema >::iterator it = Extrema3.begin(); it != Extrema3.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min3.push_back((*it).MinIndex);
		}

		for (vector< TPairedExtrema >::iterator it = Extrema4.begin(); it != Extrema4.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min4.push_back((*it).MinIndex);
		}


		for (vector< TPairedExtrema >::iterator it = Extrema5.begin(); it != Extrema5.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min5.push_back((*it).MinIndex);
		}

		for (vector< TPairedExtrema >::iterator it = Extrema6.begin(); it != Extrema6.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min6.push_back((*it).MinIndex);
		}

		//std::sort(min.begin(), min.end());

		//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
		//}
		//
		// number of submovement

		UE_LOG(LogTemp, Log, TEXT("%d"), min.size());
		UE_LOG(LogTemp, Log, TEXT("%d"), min2.size());
		UE_LOG(LogTemp, Log, TEXT("%d"), min3.size());

		ns += min.size();
		ns2 += min2.size();
		ns3 += min3.size();
		ns4 += min4.size();
		ns5 += min5.size();
		ns6 += min6.size();


		flag = true;
		Stoic = 0;
		positive = true;

		for (vector<float>::iterator it = speed.begin(); it != speed.end(); it++) {

			if (flag) {
				flag = false;
			}
			else {
				if (positive && ((*it) - before < 0)) { Stoic++; positive = false; }
				else if (!positive && ((*it) - before > 0)) { Stoic++; positive = true; }
			}
			before = *it;
		}
		fi += Stoic;

		flag = true;
		Stoic = 0;
		positive = true;

		for (vector<float>::iterator it = speed_smooth.begin(); it != speed_smooth.end(); it++) {

			if (flag) {
				flag = false;
			}
			else {
				if (positive && ((*it) - before < 0)) { Stoic++; positive = false; }
				else if (!positive && ((*it) - before > 0)) { Stoic++; positive = true; }
			}
			before = *it;
		}
		Sfi += Stoic;


		UE_LOG(LogTemp, Log, TEXT("%d"), Stoic);


		UE_LOG(LogTemp, Log, TEXT("%f,%f,%f"), ns, fi, er);

		//UKismetSystemLibrary::QuitGame(GetWorld(), SpecificPlayer1, EQuitPreference::Quit, true);

		for (int counterp = 0; counterp < 6 ; counterp++) {

			FT::DATA d;
			int TCTN = 1;
			float TCTX = TCT[counterp];


			for (int counterp2 = 0; counterp2 < ID.size(); counterp2++) {
				if (ID[counterp] == ID[counterp2] && counterp2 != counterp) {
					TCTX = TCTX + TCT[counterp2];
					TCTN++;
				}				
			}
			
			d.ID = ID[counterp];
			d.MT = TCTX / float(TCTN);
			F.load_data(d);		
		}
		
		string a = FITTS_LAW::runOptimizer();
		F.clear();

		for (int counterp = 0; counterp < 6; counterp++) {

			FT::DATA d;
			int TCTN = 1;
			float TCTX = TCTW[counterp];
			float ERX = ER[counterp];


			for (int counterp2 = 0; counterp2 < ID.size(); counterp2++) {
				if (ID[counterp] == ID[counterp2] && counterp2 != counterp) {
					ERX = ERX + ER[counterp2];
					TCTX = TCTX + TCTW[counterp2];
					TCTN++;
				}
			}
			UE_LOG(LogTemp, Log, TEXT("%d, %d, %f"), ID.size(),  TCTN , (1.0f - (ERX / float(TCTN))));
			d.ID = (1.0f - (ERX / float(TCTN))) * ID[counterp];
			d.MT = TCTX / float(TCTN);
			F.load_data(d);
		}

		string b = FITTS_LAW::runOptimizer();
		F.clear();

		for (int counterp = 0; counterp < 6; counterp++) {

			FT::DATA d;
			int TCTN = 1;
			float TCTX = TCTW[counterp];
			float sum = 0;
			float STD = 0;
			for (int counterp2 = 0; counterp2 < ID.size(); counterp2++) {
				if (ID[counterp] == ID[counterp2] && counterp2 != counterp) {					
					TCTX = TCTX + TCTW[counterp2];
					TCTN++;

					for (int counterp3 = counterp * 16; counterp3 < counterp * 16 + 16; counterp3++) {sum += W[counterp3];}
					for (int counterp4 = counterp2 * 16; counterp4 < counterp2 * 16 + 16; counterp4++) {sum += W[counterp4];}
					float avg = sum / 32.f;
					sum = 0;
					for (int counterp3 = counterp * 16; counterp3 < counterp * 16 + 16; counterp3++) { sum += pow(W[counterp3] - avg, 2); }
					for (int counterp4 = counterp2 * 16; counterp4 < counterp2 * 16 + 16; counterp4++) { sum += pow(W[counterp4] - avg, 2); }
					float variance = sum / 32.f;
					STD = sqrt(variance);
				}
			}
			d.ID = log2((D[counterp] / (STD * 4.133)) + 1);
			d.MT = TCTX / float(TCTN);
			F.load_data(d);
		}
		string c = FITTS_LAW::runOptimizer();

		speed_compare_all = 0;

		float max = *max_element(speed_raw.begin(), speed_raw.end());
		max = max / 4.0f;

		int counter_1 = 0;
		int counter_2 = 0;
		int counter_3 = 0;
		int counter_4 = 0;

		for (int counterp4 = 0; counterp4 < speed_compare.size(); counterp4++) {

			if (speed_raw[counterp4] > max * 3) {
				speed_compare_4 += speed_compare[counterp4];
				counter_4++;
			}
			else if (speed_raw[counterp4] > max * 2) {
				speed_compare_3 += speed_compare[counterp4];
				counter_3++;
			}
			else if (speed_raw[counterp4] > max * 1) {
				speed_compare_2 += speed_compare[counterp4];
				counter_2++;
			}
			else{
				speed_compare_1 += speed_compare[counterp4];
				counter_1++;
			}
		}
		speed_compare_4 = speed_compare_4 / float(counter_4);
		speed_compare_3 = speed_compare_3 / float(counter_3);
		speed_compare_2 = speed_compare_2 / float(counter_2);
		speed_compare_1 = speed_compare_1 / float(counter_1);

		a = a + ',' + b +','+ c ;

		er = 1 - (er / float(num_show_bigtrial));
		float tctTotal = 0;
		for (int conterc = 0; conterc < TCT.size(); conterc++) { tctTotal += TCT[conterc]; }
		ns = ns / tct_mouse_movement;
		ns2 = ns2 / tct_mouse_movement;
		ns3 = ns3 / tct_mouse_movement;
		ns4 = ns4 / tct_mouse_movement;
		ns5 = ns5 / tct_mouse_movement;
		ns6 = ns6 / tct_mouse_movement;
		fi = fi / tct_mouse_movement;
		Sfi = Sfi / tct_mouse_movement;

		tctTotal = tctTotal / float(TCT.size());
		a = a + string_format(",%f,%f,%f,%f", ns, fi, er, tctTotal);
		a = a + string_format(",%f,%f,%f,%f", speed_compare_4, speed_compare_3, speed_compare_2, speed_compare_1);
		ResultData = (a.c_str());
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), speed_compare_4, speed_compare_3, speed_compare_2, speed_compare_1);
		UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData);

		GameOn1 = false;
		output_file2.close();
		calculate1 = true;
		calculate = true;
	}
	

}

void AST_PointActor::BindToInput()
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("InputClick", IE_Pressed, this, &AST_PointActor::MoveToMouseCursor);
		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AST_PointActor::is_Clicked(int index)
{
	if (index == 0) {
		start_time = GetWorld()->GetTimeSeconds();
		next_click = 1;
		clicked = true;

	}
	else if (index == 3 && next_click == 1) {
		end_time = GetWorld()->GetTimeSeconds();
		resultTimeWrong += end_time - start_time;
		next_click = 0;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouse_X, mouse_Y);
		mouse_X = mouse_X - 960;
		mouse_Y = 540 - mouse_Y;
		float red_x = 960 - redx;
		float red_y = redy - 540 ;

		UE_LOG(LogTemp, Log, TEXT("%f,%f.%f.%f"), mouse_X, mouse_Y, red_x, red_y);


		if (tilt[trial] == 100) { W.push_back(abs(red_y - mouse_Y)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_y - mouse_Y)); }
		else if (tilt[trial] == 0) { W.push_back(abs(red_x - mouse_X)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_x - mouse_X)); }
		else {
			float a = red_y / red_x;
			UE_LOG(LogTemp, Log, TEXT("%f"), a);
			float c = (1 / a) * mouse_X + mouse_Y;
			float newx = c / (a + (1 / a));
			float newy = a * newx;
			W.push_back(sqrt((red_x - newx) * (red_x - newx) + (red_y - newy) * (red_y - newy)));
			UE_LOG(LogTemp, Log, TEXT("%f"), sqrt((red_x - newx) * (red_x - newx) + (red_y - newy) * (red_y - newy)));
		}
		clicked = true;
		
	}

	else {
		if (next_click == 1 && index == 1) {
			end_time = GetWorld()->GetTimeSeconds();
			write_resultTime = end_time - start_time;
			resultTimeWrong += end_time - start_time;
			resultTime += end_time - start_time;
			next_click = 0;
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouse_X, mouse_Y);
			mouse_X = mouse_X - 960;
			mouse_Y = 540 - mouse_Y;
			float red_x = 960 - redx;
			float red_y = redy - 540;

			UE_LOG(LogTemp, Log, TEXT("%f,%f.%f.%f"),mouse_X, mouse_Y, red_x, red_y);
	

			if (tilt[trial] == 100) { W.push_back(abs(red_y -mouse_Y)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_y - mouse_Y));	}
			else if (tilt[trial] == 0) { W.push_back(abs(red_x -mouse_X)); UE_LOG(LogTemp, Log, TEXT("%f"), abs(red_x - mouse_X));}
			else {
				float a = red_y / red_x ;
				UE_LOG(LogTemp, Log, TEXT("%f"), a);
				float c = (1 / a) * mouse_X + mouse_Y;
				float newx = c / (a + (1 / a));
				float newy = a * newx;
				W.push_back(sqrt((red_x - newx)*(red_x - newx) + (red_y - newy)*(red_y - newy)));
				UE_LOG(LogTemp, Log, TEXT("%f"), sqrt((red_x - newx) * (red_x - newx) + (red_y - newy) * (red_y - newy)));
			}

			clicked = true;
			trial++;
			trials++;
			blue_click = true;
			
		}

	}
		
}



void AST_PointActor::MoveToMouseCursor()
{
	boolFlag1 = false;
	FHitResult Hit;
	SpecificPlayer1->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	//UE_LOG(LogTemp, Log, TEXT("cluck"));
	if (Hit.bBlockingHit)
	{
		AActor* hitactor = Hit.GetActor();
		if (Lamps[0]->GetName() == hitactor->GetName()) {
			is_Clicked(0);
			write_hit = 1;
			
		}
		else if (Lamps[1]->GetName() == hitactor->GetName()) {
			is_Clicked(1);
			
			//바뀐부분
			string L;
			L = string_format("%f,%f,%d,%f", ballsize, writeDistance, 1, write_resultTime) + '\n';
			output_file2 << L;
			write_hit = 1;
			num_success++;			
		}		
	}
	else if (next_click == 0){		
		write_hit = 0;
		clicked = true;
	}
	else if(next_click == 1) {
		
		is_Clicked(3);
		string L;
		L = string_format("%f,%f,%d,%f", ballsize, writeDistance, 0, write_resultTime) + '\n';
		output_file2 << L;
		num_ER++;
		num_ER_total++;
		UE_LOG(LogTemp, Log, TEXT("work"));
		write_hit = 0;
	}
}

void AST_PointActor::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
}



void AST_PointActor::LoggingStart() {

	(new FAutoDeleteAsyncTask<MouseLoggingTask1>())->StartBackgroundTask();
}


//------------------------------------------------------------------------------


MouseLoggingTask1::MouseLoggingTask1() {
	UE_LOG(LogTemp, Log, TEXT("Start"));
}



MouseLoggingTask1::~MouseLoggingTask1() {
	UE_LOG(LogTemp, Log, TEXT("End"));
}


void MouseLoggingTask1::DoWork() {

	dx1 = 0;
	dy1 = 0;

	wx = {};
	wx.cbSize = sizeof(WNDCLASSEX);
	wx.lpfnWndProc = DefWindowProc;
	wx.hInstance = GetModuleHandle(NULL);
	wx.lpszClassName = TEXT("MyRawInputWndClass");

	if (!RegisterClassEx(&wx))
	{
		UE_LOG(LogTemp, Log, TEXT("failed 1"));
	}

	hWnd = CreateWindowEx(0, wx.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wx.hInstance, NULL);

	if (!hWnd)
	{
		UE_LOG(LogTemp, Log, TEXT("failed 2"));
	}

	Rid[0].usUsagePage = 0x01;
	Rid[0].usUsage = 0x02;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = hWnd;

	Rid[1].usUsagePage = 0x01;
	Rid[1].usUsage = 0x06;
	Rid[1].dwFlags = RIDEV_INPUTSINK;
	Rid[1].hwndTarget = hWnd;

	if (!RegisterRawInputDevices(Rid, 2, sizeof(RAWINPUTDEVICE)))
	{
		UE_LOG(LogTemp, Log, TEXT("failed 3"));
	}

	while (GameOn1) {

		GetMessage(&msg, NULL, 0, 0);
		//std::cout << "HERE" << std::endl;
		if (msg.message == WM_INPUT) {
			UINT dwSize = 0;
			GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
			LPBYTE lpb = new BYTE[dwSize];
			if (GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
				throw std::runtime_error("GetRawInputData does not return correct size !\n");
			RAWINPUT* raw = (RAWINPUT*)(lpb);
			//std::cout << raw->data.keyboard.Reserved << std::endl;
			if (raw->header.dwType == RIM_TYPEMOUSE) {
				dx1 += raw->data.mouse.lLastX;
				dy1 += raw->data.mouse.lLastY;
				buttonFlag1 = raw->data.mouse.usButtonFlags;
				if (buttonFlag1 == 1) { boolFlag1 = true; }
				//UE_LOG(LogTemp, Log, TEXT("%f"), dx1);
			}
			else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
			}
			HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
			// retrieve and process data from hRawInput as needed...
			//std::cout << msg.pt.x << std::endl;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
}


>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
