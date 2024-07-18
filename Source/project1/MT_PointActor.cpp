<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.


#include "MT_PointActor.h"
#include "persistence1d.hpp"
#include "windows.h"

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

#include "../../ThirdParty/pointing/pointing.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "UnrealClient.h"
#include "Components/InputComponent.h"

using namespace std;
using namespace p1d;
using namespace pointing;


float dx2 = 0;
float dy2 = 0;
float buttonFlag2 = 0;
bool boolFlag2 = false;
bool GameOn2 = true;

ofstream output_file4;
ifstream checker_file4;

//TransferFunction* func = 0;

// Sets default values
AMT_PointActor::AMT_PointActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	num_trial = 150;
	num_success = 0;
	trial = 1;
	// 픽셀 0 ~ 2000
	speed_y = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f * 96 / 100);
	speed_z = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f* 96/100);
	// 픽셀 36 ~ 90
	target_width = FMath::RandRange(36.0f*96/100, 90.0f*96 / 100);
	clicked = false;
	collided_y = collided_z = false;
	start_game = false;
	deltacount = 0;
	big_trial = 1;
	num_big_trial = 2;
	stop = false;
	realStart = false;
	GameOn2 = true;
	ns = 0;
	ns2 = 0;
	ns3 = 0;
	ns4 = 0;
	ns5 = 0;
	ns6 = 0;
	Sfi = 0;
	fi = 0;
	reactionTime2 = 0;
	MX1 = 0;
	MY1 = 0;
	framecounter = 0;
	tct_mouse_movement = 0;

	
	speed_compare_1 = 0;
	speed_compare_2 = 0;
	speed_compare_3 = 0;
	speed_compare_4 = 0;
}



template<typename ... Args> string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

// Called when the game starts or when spawned
void AMT_PointActor::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TotalActor;
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	target_z = FMath::RandRange(-(ViewportSize.Y / ViewportSize.X) * 1000 + target_width / 2, (ViewportSize.Y / ViewportSize.X) * 1000 - target_width / 2);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	
	Set2DView();
	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Sphere")) Lamp = Actor;
	}
	Lamp->SetActorScale3D(FVector(target_width / 100.0f, target_width / 100.0f, target_width / 100.0f));
	Lamp->SetActorLocation(FVector(-3000, target_y, target_z));
	start_game = true;

	string path;
	int i = 0;
	bool fileopen = false;
	GameOn2 = true;

	while (!fileopen) {
		
		path = "C:/Users/jonghyeon/Desktop/" + to_string(i) + ".csv";

		checker_file4.open(path);
		if (!checker_file4.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file4.close();
	}

	output_file4.open(path, std::ios::out | std::ios::binary);
	output_file4 << "UserID,RealTime,Round,Trial,Ballsize,Ball_X,Ball_Y,Ball_Dx,Ball_Dy,Mouse_X,Mouse_Y,Mouse_Dx,Mouse_DY,Click,Correct(Hit),ReactionTime, submovement \n";
	speed_compare.push_back(1.0);
	//BindToInput();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(cur_mouse_X, cur_mouse_Y);
	LoggingStart();
}
/*
void pointingCallback(void*, TimeStamp::inttime timestamp, int input_dx, int input_dy, int buttons) {
	int output_dx = 0, output_dy = 0;

	func->applyi(input_dx, input_dy, &output_dx, &output_dy, timestamp);
	//UE_LOG(LogTemp, Log, TEXT("speed :: (%d, %d)"), input_dx, input_dy);
}*/
// Called every frame
void AMT_PointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	/*
	if (deltacount == 1) {
		input = PointingDevice::create("any:?debugLevel=1");
		output = DisplayDevice::create("any:?debugLevel=1");
		func = TransferFunction::create("sigmoid:?debugLevel=2", input, output);
	}
	input->setPointingCallback(pointingCallback);
	*/
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	MX1 = cur_mouse_X;
	MY1 = cur_mouse_Y;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(cur_mouse_X, cur_mouse_Y);
	//UE_LOG(LogTemp, Log, TEXT("deltatime :: (%f)"), 1/ DeltaTime);
	framecounter=  framecounter + DeltaTime;
	//UE_LOG(LogTemp, Log, TEXT("counter :: (%f)"), framecounter);
	/*
	mouse_speed = FMath::Sqrt((cur_mouse_X - mouse_X) * (cur_mouse_X - mouse_X) + (cur_mouse_Y - mouse_Y) * (cur_mouse_Y - mouse_Y)) / (DeltaTime ) ;
	speed.push_back(mouse_speed);
	mouse_speed_vector = FVector2D((cur_mouse_X - mouse_X) / (DeltaTime), (cur_mouse_Y - mouse_Y) / (DeltaTime));
	*/


	//UE_LOG(LogTemp, Log, TEXT("speed :: (%f)"), mouse_speed);
	//UE_LOG(LogTemp, Log, TEXT("speed :: (%f, %f)"), mouse_speed_vector.X, mouse_speed_vector.Y);
	
	/*
	mouse_X = cur_mouse_X;
	mouse_Y = cur_mouse_Y;
	*/
	if (start_game && !stop && realStart) RepeatingFunc();

	if (boolFlag2 && !stop && realStart) { MoveToMouseCursor(); }
	else boolFlag2 = false;

	if (stop) clicked = false;
	if (!realStart) realStart = true;

	FVector Cur_location = Lamp->GetActorLocation();
	Cur_location.Y += speed_y * DeltaTime;
	Cur_location.Z += speed_z * DeltaTime;

	Lamp->SetActorLocation(Cur_location);
	if (Cur_location.Y > 1000 - target_width / 2 || Cur_location.Y < -1000 + target_width / 2) collided_y = true;
	else collided_y = false;
	if (Cur_location.Z > (ViewportSize.Y / ViewportSize.X) * 1000 - target_width / 2 || Cur_location.Z < -(ViewportSize.Y / ViewportSize.X) * 1000 + target_width / 2) collided_z = true;
	else collided_z = false;

	if (collided_y) speed_y = -speed_y;
	if (collided_z) speed_z = -speed_z;

	//UE_LOG(LogTemp, Log, TEXT("Current Location (%f, %f)"), Cur_location.Y, Cur_location.Z);

	std::string userIDString(TCHAR_TO_UTF8(*userID));
	string L;
	//UE_LOG(LogTemp, Log, TEXT("%f,%f"), MX, MY);
	timenow = GetWorld()->GetTimeSeconds();
	L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f", timenow,big_trial, trial, target_width / 1000 * 960 , -(Cur_location.Y / 1000 * 960) + 960, -(Cur_location.Z / 1000 * 960) + 540, speed_y / 1000 * 960, speed_z / 1000 * 960, cur_mouse_X, cur_mouse_Y, dx2, dy2, clicked, num_success, reactionTime) + '\n';
	output_file4 << L;
	//UE_LOG(LogTemp, Log, TEXT("(%d, %d)"), big_trial, trial);
	mouse_speed = sqrt(dx2*dx2 + dy2*dy2) / (DeltaTime*1000.0f);
	if (sqrt((cur_mouse_X - MX1) * (cur_mouse_X - MX1) + (cur_mouse_Y - MY1) * (cur_mouse_Y - MY1)) != 0 && mouse_speed != 0) {
		mouse_speed_compare = sqrt((cur_mouse_X - MX1) * (cur_mouse_X - MX1) + (cur_mouse_Y - MY1) * (cur_mouse_Y - MY1)) / sqrt(dx2 * dx2 + dy2 * dy2);
	}
	
	//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);
	if (!stop) { 
		UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
		speed.push_back(mouse_speed);
		if (mouse_speed > 0) { tct_mouse_movement += DeltaTime; }
		if (mouse_speed_compare != speed_compare[speed_compare.size() - 1] && !((cur_mouse_X > 1910 && MX1 > 1910) || (MY1 > 1070 && cur_mouse_Y > 1070) || (MY1 < 10 && cur_mouse_Y < 10) || (cur_mouse_X < 10 && MX1 < 10))) {
			//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);
			speed_compare.push_back(mouse_speed_compare); 
			speed_raw.push_back(mouse_speed);	
		}
		
	}
	dx2 = 0;
	dy2 = 0;
	reactionTime = 0;
	//BindToInput();



	if (trial == num_trial+1)
	{	
		trial =1;
		big_trial++;
		stop = true;


		er += num_success / float(num_trial);
		num_success = 0;

		tct += reactionTime2 / float(num_trial);
		reactionTime2 = 0;


		//end_time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Log, TEXT("time :: %f seconds"), end_time - start_time);

		
		
	}


	if (big_trial == num_big_trial + 1) {
		big_trial++;
		stop = true;
		datasended = true;
		start_game = false;


		float maximum = *max_element(speed.begin(), speed.end());
		float minimum = *min_element(speed.begin(), speed.end());

		for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) { speed_normalize.push_back((speed[speed_counter] - minimum) / (maximum - minimum)); }
		for (int speed_counter2 = 1; speed_counter2 < speed_normalize.size() - 1; speed_counter2++) { speed_smooth.push_back(speed_normalize[speed_counter2 - 1] * 0.27901 + speed_normalize[speed_counter2] * 0.44198 + speed_normalize[speed_counter2 + 1] * 0.27901); }

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
		/*
		std::stringstream ss;
		for (auto it2 = min2.begin(); it2 != min2.end(); it2++) {
			if (it2 != min2.begin()) { ss << " "; }
			ss << *it2;
		}
		output_file4 << ss.str() + "\n";



		std::stringstream ss2;
		for (auto it3 = speed_normalize.begin(); it3 != speed_normalize.end(); it3++) {
			if (it3 != speed_normalize.begin()) { ss2 << " "; }
			ss2 << *it3;
	}

	output_file4 << ss2.str();
	*/






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

		ns = ns / tct_mouse_movement;
		ns2 = ns2 / tct_mouse_movement;
		ns3 = ns3 / tct_mouse_movement;
		ns4 = ns4 / tct_mouse_movement;
		ns5 = ns5 / tct_mouse_movement;
		ns6 = ns6 / tct_mouse_movement;
		fi = fi / tct_mouse_movement;
		Sfi = Sfi / tct_mouse_movement;
		tct = tct / float(num_big_trial);
		er = 1 - (er / float(num_big_trial));

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
			else {
				speed_compare_1 += speed_compare[counterp4];
				counter_1++;
			}
		}
		speed_compare_4 = speed_compare_4 / float(counter_4);
		speed_compare_3 = speed_compare_3 / float(counter_3);
		speed_compare_2 = speed_compare_2 / float(counter_2);
		speed_compare_1 = speed_compare_1 / float(counter_1);

		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f, %f, %f"), ns, ns2, ns3, fi, tct, er);
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), speed_compare_4, speed_compare_3, speed_compare_2, speed_compare_1);

		output_file4.close();
		GameOn2 = false;
	}
}


void AMT_PointActor::RepeatingFunc() //클릭하면 새로 생성
{
	//UE_LOG(LogTemp, Log, TEXT("RPF"));
	if (clicked) {
		end_time = GetWorld()->GetTimeSeconds();
		reactionTime = end_time - start_time;
		reactionTime2 += reactionTime;
		//UE_LOG(LogTemp, Log, TEXT("react time :: %f seconds"), end_time - start_time);
		// 픽셀 0 ~ 2000
		speed_y = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f * 96 / 100);
		speed_z = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f * 96 / 100);
		// 픽셀 36 ~ 90
		target_width = FMath::RandRange(36.0f * 96 / 100, 90.0f * 96 / 100);
		target_y = FMath::RandRange(-1000 + target_width / 2, 1000 - + target_width / 2);
		target_z = FMath::RandRange(-(ViewportSize.Y / ViewportSize.X) * 1000 + target_width / 2, +(ViewportSize.Y / ViewportSize.X) * 1000 - target_width / 2); 
		Lamp->SetActorScale3D(FVector(target_width / 100.0f, target_width / 100.0f, target_width / 100.0f));
		Lamp->SetActorLocation(FVector(-3000, target_y, target_z));
		start_time = GetWorld()->GetTimeSeconds();
		clicked = false;
		collided_y = false;
		collided_z = false;
	}
}

void AMT_PointActor::BindToInput()
{
	// Initialize our component


	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();


	if (InputComponent)
	{
		InputComponent->BindAction("InputClick", IE_Pressed, this, &AMT_PointActor::MoveToMouseCursor);
		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AMT_PointActor::MoveToMouseCursor()
{
	//UE_LOG(LogTemp, Log, TEXT("MTC"));

	FHitResult Hit;
	SpecificPlayer1->GetHitResultUnderCursor(ECC_Visibility, false, Hit);


	if (framecounter > 0.2f) {
		trial++; 
		framecounter = 0;
	

		clicked = true;

		if (Hit.bBlockingHit)
		{
			AActor* hitactor = Hit.GetActor();
			if (Lamp->GetName() == hitactor->GetName()) num_success++;
		}
		//UE_LOG(LogTemp, Log, TEXT("%d"), num_success);
		
	}
	boolFlag2 = false;

}

void AMT_PointActor::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
}



void AMT_PointActor::GetTime() {
	start_time = GetWorld()->GetTimeSeconds();
}

void AMT_PointActor::LoggingStart() {

	(new FAutoDeleteAsyncTask<MouseLoggingTask2>())->StartBackgroundTask();
}


//------------------------------------------------------------------------------


MouseLoggingTask2::MouseLoggingTask2() {
	UE_LOG(LogTemp, Log, TEXT("Start"));
}



MouseLoggingTask2::~MouseLoggingTask2() {
	UE_LOG(LogTemp, Log, TEXT("End"));
}


void MouseLoggingTask2::DoWork() {

	dx2 = 0;
	dy2 = 0;
	
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

	while (GameOn2) {

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
				dx2 += raw->data.mouse.lLastX;
				dy2 += raw->data.mouse.lLastY;
				buttonFlag2 = raw->data.mouse.usButtonFlags;
				if (buttonFlag2 == 1) { boolFlag2 = true; }
				
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
=======
// Fill out your copyright notice in the Description page of Project Settings.


#include "MT_PointActor.h"
#include "persistence1d.hpp"
#include "windows.h"

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

#include "../../ThirdParty/pointing/pointing.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "UnrealClient.h"
#include "Components/InputComponent.h"

using namespace std;
using namespace p1d;
using namespace pointing;


float dx2 = 0;
float dy2 = 0;
float buttonFlag2 = 0;
bool boolFlag2 = false;
bool GameOn2 = true;

ofstream output_file4;
ifstream checker_file4;

//TransferFunction* func = 0;

// Sets default values
AMT_PointActor::AMT_PointActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	num_trial = 150;
	num_success = 0;
	trial = 1;
	// 픽셀 0 ~ 2000
	speed_y = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f * 96 / 100);
	speed_z = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f* 96/100);
	// 픽셀 36 ~ 90
	target_width = FMath::RandRange(36.0f*96/100, 90.0f*96 / 100);
	clicked = false;
	collided_y = collided_z = false;
	start_game = false;
	deltacount = 0;
	big_trial = 1;
	num_big_trial = 2;
	stop = false;
	realStart = false;
	GameOn2 = true;
	ns = 0;
	ns2 = 0;
	ns3 = 0;
	ns4 = 0;
	ns5 = 0;
	ns6 = 0;
	Sfi = 0;
	fi = 0;
	reactionTime2 = 0;
	MX1 = 0;
	MY1 = 0;
	framecounter = 0;
	tct_mouse_movement = 0;

	
	speed_compare_1 = 0;
	speed_compare_2 = 0;
	speed_compare_3 = 0;
	speed_compare_4 = 0;
}



template<typename ... Args> string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

// Called when the game starts or when spawned
void AMT_PointActor::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TotalActor;
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	target_z = FMath::RandRange(-(ViewportSize.Y / ViewportSize.X) * 1000 + target_width / 2, (ViewportSize.Y / ViewportSize.X) * 1000 - target_width / 2);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	
	Set2DView();
	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Sphere")) Lamp = Actor;
	}
	Lamp->SetActorScale3D(FVector(target_width / 100.0f, target_width / 100.0f, target_width / 100.0f));
	Lamp->SetActorLocation(FVector(-3000, target_y, target_z));
	start_game = true;

	string path;
	int i = 0;
	bool fileopen = false;
	GameOn2 = true;

	while (!fileopen) {
		
		path = "C:/Users/jonghyeon/Desktop/" + to_string(i) + ".csv";

		checker_file4.open(path);
		if (!checker_file4.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file4.close();
	}

	output_file4.open(path, std::ios::out | std::ios::binary);
	output_file4 << "UserID,RealTime,Round,Trial,Ballsize,Ball_X,Ball_Y,Ball_Dx,Ball_Dy,Mouse_X,Mouse_Y,Mouse_Dx,Mouse_DY,Click,Correct(Hit),ReactionTime, submovement \n";
	speed_compare.push_back(1.0);
	//BindToInput();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(cur_mouse_X, cur_mouse_Y);
	LoggingStart();
}
/*
void pointingCallback(void*, TimeStamp::inttime timestamp, int input_dx, int input_dy, int buttons) {
	int output_dx = 0, output_dy = 0;

	func->applyi(input_dx, input_dy, &output_dx, &output_dy, timestamp);
	//UE_LOG(LogTemp, Log, TEXT("speed :: (%d, %d)"), input_dx, input_dy);
}*/
// Called every frame
void AMT_PointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	/*
	if (deltacount == 1) {
		input = PointingDevice::create("any:?debugLevel=1");
		output = DisplayDevice::create("any:?debugLevel=1");
		func = TransferFunction::create("sigmoid:?debugLevel=2", input, output);
	}
	input->setPointingCallback(pointingCallback);
	*/
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	MX1 = cur_mouse_X;
	MY1 = cur_mouse_Y;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(cur_mouse_X, cur_mouse_Y);
	//UE_LOG(LogTemp, Log, TEXT("deltatime :: (%f)"), 1/ DeltaTime);
	framecounter=  framecounter + DeltaTime;
	//UE_LOG(LogTemp, Log, TEXT("counter :: (%f)"), framecounter);
	/*
	mouse_speed = FMath::Sqrt((cur_mouse_X - mouse_X) * (cur_mouse_X - mouse_X) + (cur_mouse_Y - mouse_Y) * (cur_mouse_Y - mouse_Y)) / (DeltaTime ) ;
	speed.push_back(mouse_speed);
	mouse_speed_vector = FVector2D((cur_mouse_X - mouse_X) / (DeltaTime), (cur_mouse_Y - mouse_Y) / (DeltaTime));
	*/


	//UE_LOG(LogTemp, Log, TEXT("speed :: (%f)"), mouse_speed);
	//UE_LOG(LogTemp, Log, TEXT("speed :: (%f, %f)"), mouse_speed_vector.X, mouse_speed_vector.Y);
	
	/*
	mouse_X = cur_mouse_X;
	mouse_Y = cur_mouse_Y;
	*/
	if (start_game && !stop && realStart) RepeatingFunc();

	if (boolFlag2 && !stop && realStart) { MoveToMouseCursor(); }
	else boolFlag2 = false;

	if (stop) clicked = false;
	if (!realStart) realStart = true;

	FVector Cur_location = Lamp->GetActorLocation();
	Cur_location.Y += speed_y * DeltaTime;
	Cur_location.Z += speed_z * DeltaTime;

	Lamp->SetActorLocation(Cur_location);
	if (Cur_location.Y > 1000 - target_width / 2 || Cur_location.Y < -1000 + target_width / 2) collided_y = true;
	else collided_y = false;
	if (Cur_location.Z > (ViewportSize.Y / ViewportSize.X) * 1000 - target_width / 2 || Cur_location.Z < -(ViewportSize.Y / ViewportSize.X) * 1000 + target_width / 2) collided_z = true;
	else collided_z = false;

	if (collided_y) speed_y = -speed_y;
	if (collided_z) speed_z = -speed_z;

	//UE_LOG(LogTemp, Log, TEXT("Current Location (%f, %f)"), Cur_location.Y, Cur_location.Z);

	std::string userIDString(TCHAR_TO_UTF8(*userID));
	string L;
	//UE_LOG(LogTemp, Log, TEXT("%f,%f"), MX, MY);
	timenow = GetWorld()->GetTimeSeconds();
	L = userIDString + "," + string_format("%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f", timenow,big_trial, trial, target_width / 1000 * 960 , -(Cur_location.Y / 1000 * 960) + 960, -(Cur_location.Z / 1000 * 960) + 540, speed_y / 1000 * 960, speed_z / 1000 * 960, cur_mouse_X, cur_mouse_Y, dx2, dy2, clicked, num_success, reactionTime) + '\n';
	output_file4 << L;
	//UE_LOG(LogTemp, Log, TEXT("(%d, %d)"), big_trial, trial);
	mouse_speed = sqrt(dx2*dx2 + dy2*dy2) / (DeltaTime*1000.0f);
	if (sqrt((cur_mouse_X - MX1) * (cur_mouse_X - MX1) + (cur_mouse_Y - MY1) * (cur_mouse_Y - MY1)) != 0 && mouse_speed != 0) {
		mouse_speed_compare = sqrt((cur_mouse_X - MX1) * (cur_mouse_X - MX1) + (cur_mouse_Y - MY1) * (cur_mouse_Y - MY1)) / sqrt(dx2 * dx2 + dy2 * dy2);
	}
	
	//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);
	if (!stop) { 
		UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed);
		speed.push_back(mouse_speed);
		if (mouse_speed > 0) { tct_mouse_movement += DeltaTime; }
		if (mouse_speed_compare != speed_compare[speed_compare.size() - 1] && !((cur_mouse_X > 1910 && MX1 > 1910) || (MY1 > 1070 && cur_mouse_Y > 1070) || (MY1 < 10 && cur_mouse_Y < 10) || (cur_mouse_X < 10 && MX1 < 10))) {
			//UE_LOG(LogTemp, Log, TEXT("(%f)"), mouse_speed_compare);
			speed_compare.push_back(mouse_speed_compare); 
			speed_raw.push_back(mouse_speed);	
		}
		
	}
	dx2 = 0;
	dy2 = 0;
	reactionTime = 0;
	//BindToInput();



	if (trial == num_trial+1)
	{	
		trial =1;
		big_trial++;
		stop = true;


		er += num_success / float(num_trial);
		num_success = 0;

		tct += reactionTime2 / float(num_trial);
		reactionTime2 = 0;


		//end_time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Log, TEXT("time :: %f seconds"), end_time - start_time);

		
		
	}


	if (big_trial == num_big_trial + 1) {
		big_trial++;
		stop = true;
		datasended = true;
		start_game = false;


		float maximum = *max_element(speed.begin(), speed.end());
		float minimum = *min_element(speed.begin(), speed.end());

		for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) { speed_normalize.push_back((speed[speed_counter] - minimum) / (maximum - minimum)); }
		for (int speed_counter2 = 1; speed_counter2 < speed_normalize.size() - 1; speed_counter2++) { speed_smooth.push_back(speed_normalize[speed_counter2 - 1] * 0.27901 + speed_normalize[speed_counter2] * 0.44198 + speed_normalize[speed_counter2 + 1] * 0.27901); }

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
		/*
		std::stringstream ss;
		for (auto it2 = min2.begin(); it2 != min2.end(); it2++) {
			if (it2 != min2.begin()) { ss << " "; }
			ss << *it2;
		}
		output_file4 << ss.str() + "\n";



		std::stringstream ss2;
		for (auto it3 = speed_normalize.begin(); it3 != speed_normalize.end(); it3++) {
			if (it3 != speed_normalize.begin()) { ss2 << " "; }
			ss2 << *it3;
	}

	output_file4 << ss2.str();
	*/






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

		ns = ns / tct_mouse_movement;
		ns2 = ns2 / tct_mouse_movement;
		ns3 = ns3 / tct_mouse_movement;
		ns4 = ns4 / tct_mouse_movement;
		ns5 = ns5 / tct_mouse_movement;
		ns6 = ns6 / tct_mouse_movement;
		fi = fi / tct_mouse_movement;
		Sfi = Sfi / tct_mouse_movement;
		tct = tct / float(num_big_trial);
		er = 1 - (er / float(num_big_trial));

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
			else {
				speed_compare_1 += speed_compare[counterp4];
				counter_1++;
			}
		}
		speed_compare_4 = speed_compare_4 / float(counter_4);
		speed_compare_3 = speed_compare_3 / float(counter_3);
		speed_compare_2 = speed_compare_2 / float(counter_2);
		speed_compare_1 = speed_compare_1 / float(counter_1);

		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f, %f, %f"), ns, ns2, ns3, fi, tct, er);
		UE_LOG(LogTemp, Log, TEXT("%f, %f, %f, %f"), speed_compare_4, speed_compare_3, speed_compare_2, speed_compare_1);

		output_file4.close();
		GameOn2 = false;
	}
}


void AMT_PointActor::RepeatingFunc() //클릭하면 새로 생성
{
	//UE_LOG(LogTemp, Log, TEXT("RPF"));
	if (clicked) {
		end_time = GetWorld()->GetTimeSeconds();
		reactionTime = end_time - start_time;
		reactionTime2 += reactionTime;
		//UE_LOG(LogTemp, Log, TEXT("react time :: %f seconds"), end_time - start_time);
		// 픽셀 0 ~ 2000
		speed_y = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f * 96 / 100);
		speed_z = FMath::RandRange(-1000.0f * 96 / 100, 1000.0f * 96 / 100);
		// 픽셀 36 ~ 90
		target_width = FMath::RandRange(36.0f * 96 / 100, 90.0f * 96 / 100);
		target_y = FMath::RandRange(-1000 + target_width / 2, 1000 - + target_width / 2);
		target_z = FMath::RandRange(-(ViewportSize.Y / ViewportSize.X) * 1000 + target_width / 2, +(ViewportSize.Y / ViewportSize.X) * 1000 - target_width / 2); 
		Lamp->SetActorScale3D(FVector(target_width / 100.0f, target_width / 100.0f, target_width / 100.0f));
		Lamp->SetActorLocation(FVector(-3000, target_y, target_z));
		start_time = GetWorld()->GetTimeSeconds();
		clicked = false;
		collided_y = false;
		collided_z = false;
	}
}

void AMT_PointActor::BindToInput()
{
	// Initialize our component


	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();


	if (InputComponent)
	{
		InputComponent->BindAction("InputClick", IE_Pressed, this, &AMT_PointActor::MoveToMouseCursor);
		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AMT_PointActor::MoveToMouseCursor()
{
	//UE_LOG(LogTemp, Log, TEXT("MTC"));

	FHitResult Hit;
	SpecificPlayer1->GetHitResultUnderCursor(ECC_Visibility, false, Hit);


	if (framecounter > 0.2f) {
		trial++; 
		framecounter = 0;
	

		clicked = true;

		if (Hit.bBlockingHit)
		{
			AActor* hitactor = Hit.GetActor();
			if (Lamp->GetName() == hitactor->GetName()) num_success++;
		}
		//UE_LOG(LogTemp, Log, TEXT("%d"), num_success);
		
	}
	boolFlag2 = false;

}

void AMT_PointActor::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
}



void AMT_PointActor::GetTime() {
	start_time = GetWorld()->GetTimeSeconds();
}

void AMT_PointActor::LoggingStart() {

	(new FAutoDeleteAsyncTask<MouseLoggingTask2>())->StartBackgroundTask();
}


//------------------------------------------------------------------------------


MouseLoggingTask2::MouseLoggingTask2() {
	UE_LOG(LogTemp, Log, TEXT("Start"));
}



MouseLoggingTask2::~MouseLoggingTask2() {
	UE_LOG(LogTemp, Log, TEXT("End"));
}


void MouseLoggingTask2::DoWork() {

	dx2 = 0;
	dy2 = 0;
	
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

	while (GameOn2) {

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
				dx2 += raw->data.mouse.lLastX;
				dy2 += raw->data.mouse.lLastY;
				buttonFlag2 = raw->data.mouse.usButtonFlags;
				if (buttonFlag2 == 1) { boolFlag2 = true; }
				
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
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
}