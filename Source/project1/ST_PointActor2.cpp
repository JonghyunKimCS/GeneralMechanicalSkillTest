<<<<<<< HEAD
/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ST_PointActor2.h"

#include "../../ThirdParty/pointing/pointing.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <Lmcons.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string.h>
#include <io.h>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <tchar.h>  
//#include "optimizer1.h"

#include "persistence1d.hpp"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"

using namespace std;
using namespace p1d;

//using namespace p1d;
//using namespace pointing;

//TransferFunction* func = 0;

ofstream R2file;
ifstream checkfile;
ifstream checkfile1;
ifstream checkfile2;


/*
static HMODULE g_hModule;
static HMODULE g_hModule2;
static HHOOK g_hKeyboard;
static HHOOK g_hMouse;
static HHOOK g_hHook;
static HHOOK g_hHook2;
*/

float dx = 0;
float dy = 0;
bool GameOn = true;

/*
WNDCLASSEX wx;
HWND hWnd;
RAWINPUTDEVICE Rid[2];
*/
//int click = 0;


string path = "C:/Users/jonghyeon/Desktop/Data_5/1/Reaction_0.csv";
// paaaaaaaaaaaaaaaaaaaaaaaaa
string path2 = "C:/Users/jonghyeon/Desktop/Data_5/Reaction_R2/reaction_R2_1.csv";

vector<string> split(string str, char delimiter);

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		answer.push_back(temp);
	}

	return answer;
}

/*
string base = ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,";
string base1 = "";
string base2 = "";
*/
// Sets default values
AST_PointActor2::AST_PointActor2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//result_time2 = 0;
	//result_time1 = 0;
	//counter = 0;	

}
/*
template<typename ... Args> string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
*/
/*
void pointingCallback1(void*, TimeStamp::inttime timestamp, int input_dx, int input_dy, int buttons) {
	int output_dx = 0, output_dy = 0;

	func->applyi(input_dx, input_dy, &output_dx, &output_dy, timestamp);

	dx += input_dx;
	dy += input_dy;
	click = buttons;
}
*/
/*
const string TCHAR_TO_STRING(const TCHAR* a) {
	int len = wcslen((wchar_t*)a);
	char* b = new char[2 * len + 1];
	wcstombs(b, (wchar_t*)a, 2 * len + 1);
	string s = b;
	delete[] b;
	return s;
}
*/

// Called when the game starts or when spawned
void AST_PointActor2::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	
	string line;

	/*
	speedset.push_back(0);
	speedset.push_back(0);
	
	POINT pt;
	GetCursorPos(&pt);

	cur_mouse_X = pt.x;
	cur_mouse_Y = pt.y;
	cur_mouse_X2 = pt.x;
	cur_mouse_Y2 = pt.y;

	input = PointingDevice::create("any:?debugLevel=1");
	output = DisplayDevice::create("any:?debugLevel=1");
	func = TransferFunction::create("sigmoid:?debugLevel=2", input, output);	
	input->setPointingCallback(pointingCallback1);	
	*/


	/*
	TCHAR username[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)username, &size);
	string usernameString = TCHAR_TO_STRING(username);
	string path = "C:/Users/" + usernameString +"/Desktop/Logging.csv";
	output_file.open(path, std::ios::out | std::ios::binary);
	output_file << "Timestamp,dx,dy,leftclick,rightclick, cursor_x,cursor_y,Esc,1,2,3,4,5,6,7,8,9,0,-,=,backspace,tab,Q,W,E,R,T,Y,U,I,O,P,[,],Enter,Ctrl,A,S,D,F,G,H,J,K,L,;,',Lshift,`,\\,Z,X,C,V,B,N,M,comma,.,/,Rshift,PrtSc,Alt,Space,Caps,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NumLock,ScrollLock,Home,Up,PgUp,-,Left,Center,Right,+,End,Down,PgDn,Ins,Del,84,85,86,F11,F12,speed\n";
	start_time = GetWorld()->GetTimeSeconds();
	LoggingStart();
	*/
	//BindToInput();

	//SetHook();	
	/*
	
	float n1 = 0.0f;
	float n2 = 0.0f;
	float n3 = 0.0f;
	//6 con 5 round
	// paaaaaaaaaaaaaaaaaaaaaaaaa
	int num_light =0;

	path2 = "C:/Users/jonghyeon/Desktop/Data_5/Reaction_R2/DD_R2_ToTal.csv";
	R2file.open(path2, ios::out);
	int i = 1;
	int k;
	while (i < 6) {		
		
		int j = 1;
		while (j < 101) {
			path = "C:/Users/jonghyeon/Desktop/Data_5/"+to_string(i)+ "/Reaction_0.csv";
			checkfile.open(path, ios::in);
			getline(checkfile, line);
			D.clear();

			k = 0;
			while (k < 3) {
				int p = j;
				int q = 100 - j;

				while (p > 0) {
					getline(checkfile, line);
					vector<string> result = split(line, ',');

					DD::DATA d;
					d.RT = stof(result[8]);
					d.COR = stoi(result[5]);
					D.load_data(d);
					p--;
				
				}

				while (q > 0) {
					getline(checkfile, line);
					q--;
				}
				
				k++;
								
			}	
			string a = DRIFT_DIFFUSION_MODEL::runOptimizer();
			UE_LOG(LogTemp, Log, TEXT("(dobby is free)"));
			R2file << a ;

			checkfile.close();
			j++;		
		}
		i++;
	}

	R2file.close();
	*/
	


	/*
	
	DD::DATA d;
	d.RT = react_time;
	d.COR = isCorrect;
	D.load_data(d);


	HC::DATA d;
	d.N = num_lamp;
	d.RT = (total_react_time / num_trial);
	H.load_data(d);
	
	string a = HICKS_LAW::runOptimizer();
	while (i <6) {

		n1 = 0.0f;
		n2 = 0.0f;

		HC::DATA d;
		int f = 0;
		int c1 = 0;
		
		int c2 = 16;


		while (f < 16) {

			getline(checkfile, line);
			vector<string> result = split(line, ',');				
			
			n1 = stof(result[0]);

			if (c1 < c2) { n2 += stof(result[1]);}	
			c1++;
			f++;
		
		}
		d.ID = n1;
		d.MT = n2 / float(c2);

		F.load_data(d);
		
		if (stof(result[18]) != 0) {

			n1 = stof(result[18]);
			n2 = stof(result[6]);
			string a3;

			if (n2 > 6.33) { a3 = '1'; }
			else if (n2 > 5.35) {
				if (stof(result[4]) > 15) { a3 = '2'; }
				else { a3 = '3'; }}
			else if (n2 > 4.79) { a3 = '4'; }
			else if (n2 > 4.39) { a3 = '5'; }
			else { a3 = '6'; }


			string a1 = to_string(n2);
			string a2 = to_string(n1);

			R2file << a1 << "," << a2 << "," << a3 << "\n";
		}
		//if (stof(result[5]) > 0.1) { n3++; }

		//float q1 = n1 / float(n2);
		//float q2 = n3 / float(n2);
		
		//if (n2 == 100) {n1 = 0; n2 = 0; n3 = 0;	}
	
		
		i++;
				
	}
	string a = HICKS_LAW::runOptimizer();
	*/
/*
	float n1 = 0.0f;
	float n2 = 0.0f;
	float n3 = 0.0f;
	float n4 = 0.0f;
	float n5 = 0.0f;
	float n6 = 0.0f;

	float e1 = 0.0f;
	float e2 = 0.0f;
	float e3 = 0.0f;
	float e4 = 0.0f;
	float e5 = 0.0f;
	float e6 = 0.0f;
	int i = 3;
	//조건 끝까지{}
	path2 = "C:/Users/jonghyeon/Desktop/Data_5/stp_ER2/R2_" + to_string(i) + ".csv";
	R2file.open(path2, ios::out);

	path = path2 = "C:/Users/jonghyeon/Desktop/Data_5/stp_ER2/ER2_" + to_string(i) + ".csv";
	checkfile1.open(path, ios::in);
	path = "C:/Users/jonghyeon/Desktop/Data_5/stp_ER2/ft_" + to_string(i) + ".csv";
	checkfile2.open(path, ios::in);

	int j = 0;

	while (j < 80) {
		j++;

		getline(checkfile1, line);
		vector<string> result1 = split(line, ',');

		getline(checkfile2, line);
		vector<string> result2 = split(line, ',');


		n1 += stof(result2[1]);
		n2 += stof(result2[3]);
		n3 += stof(result2[5]);
		n4 += stof(result2[7]);
		n5 += stof(result2[9]);
		n6 += stof(result2[11]);
		e1 = stof(result1[0]);
		e2 = stof(result1[1]);
		e3 = stof(result1[2]);
		e4 = stof(result1[3]);
		e5 = stof(result1[4]);
		e6 = stof(result1[5]);

		FT::DATA d;
		d.ID = e1 * stof(result2[0]);
		d.MT = n1 / float(j);

		F.load_data(d);

		FT::DATA d2;
		d2.ID = e2 * stof(result2[2]);
		d2.MT = n2 / float(j);

		F.load_data(d2);

		FT::DATA d3;
		d3.ID = e4 * stof(result2[6]);
		d3.MT = n4 / float(j);
		F.load_data(d3);


		FT::DATA d4;
		d4.ID = e5 * stof(result2[8]);
		d4.MT = n5 / float(j);

		F.load_data(d4);

		FT::DATA d5;
		d5.ID = e6 * stof(result2[10]);
		d5.MT = n6 / float(j);
		F.load_data(d5);


		string cv = FITTS_LAW::runOptimizer();
		R2file << cv;
		F.clear();
	}

	R2file.close();
	checkfile1.close();
	checkfile2.close();
*/
/*
	float number_normalize = 0.0001;
	int i = 5;
	
	path2 ="C:/Users/jonghyeon/Desktop/Data_5/mtp"+to_string(number_normalize) +".csv";
	R2file.open(path2, ios::out);

	path ="C:/Users/jonghyeon/Desktop/Data_5/"+to_string(i)+"/MTP_0.csv";
	checkfile1.open(path, ios::in);
	getline(checkfile1, line);

	int j = 1;
	float time_before = 0;
	float time_now = 0;
	int next_click = 0;
	float tct_Total = 0;

	std::vector< float > speed;
	std::vector< float > speed_normalize;
	std::vector<int> min;
	float dx8=0;
	float dy8=0;
	float mouse_speed;
	float ns=0;
	float fi=0;
	bool flag;
	float Stoic =0;


	while (j < 114905) {	

		getline(checkfile1, line);
		vector<string> result1 = split(line, ',');

		time_now = stof(result1[1]);
		dx8 = stof(result1[12]);
		dy8 = stof(result1[11]);
		mouse_speed = sqrt(dx8 * dx8 + dy8 * dy8);
		
		if (stoi(result1[3]) != 1) {
			if (mouse_speed > 0) {
				speed.push_back(mouse_speed);
				tct_Total += time_now - time_before;
			}
			
		}
		time_before = time_now;
		j++;
	}

	float maximum = *max_element(speed.begin(), speed.end());
	float minimum = *min_element(speed.begin(), speed.end());


	for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) { 
	speed_normalize.push_back((speed[speed_counter] - minimum) / (maximum - minimum));	
	}

	Persistence1D p;
	p.RunPersistence(speed_normalize);

	vector< TPairedExtrema > Extrema;
	p.GetPairedExtrema(Extrema, number_normalize);

	for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
	{
		//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
		min.push_back((*it).MinIndex);
	}


	//std::sort(min.begin(), min.end());

	//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
	//}
	//
	// number of submovement
	UE_LOG(LogTemp, Log, TEXT("%d"), min.size());
	UE_LOG(LogTemp, Log, TEXT("%d"), min.size());
	ns += min.size();

	flag = true;
	Stoic = 0;
	bool positive = true;
	float before = 0;

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
	UE_LOG(LogTemp, Log, TEXT("%f"), tct_Total);
	ns = ns / tct_Total;
	fi = fi / tct_Total;

	R2file << number_normalize<< ',' << ns << ',' << fi << ',' << min.size() << ',' << speed_normalize.size() << '\n';
	checkfile1.close();



	

	while (number_normalize < 1) {
		number_normalize += 0.0001;
		min = {};
		ns = 0;
		fi = 0;
		Extrema = {};

		p.RunPersistence(speed_normalize);
		p.GetPairedExtrema(Extrema, number_normalize);

		for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min.push_back((*it).MinIndex);
		}


		//std::sort(min.begin(), min.end());

		//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
		//}
		//
		// number of submovement
		ns += min.size();

		flag = true;
		Stoic = 0;
		positive = true;
		before = 0;

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
		ns = ns / tct_Total;
		fi = fi / tct_Total;

		R2file << number_normalize << ',' << ns << ',' << fi << ',' << min.size() << ',' << speed_normalize.size() << '\n';
	}
	R2file.close();


	number_normalize = 0.1;
	path2 = "C:/Users/jonghyeon/Desktop/Data_5/mtp" + to_string(number_normalize) + ".csv";
	R2file.open(path2, ios::out);


	while (number_normalize < 100) {
		
		min = {};
		ns = 0;
		fi = 0;
		Extrema = {};

		p.RunPersistence(speed);
		p.GetPairedExtrema(Extrema, number_normalize);

		for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min.push_back((*it).MinIndex);
		}


		//std::sort(min.begin(), min.end());

		//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
		//}
		//
		// number of submovement
		ns += min.size();

		flag = true;
		Stoic = 0;
		positive = true;
		before = 0;

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
		ns = ns / tct_Total;
		fi = fi / tct_Total;

		R2file << number_normalize << ',' << ns << ',' << fi << ',' << min.size() << ',' << speed_normalize.size() << '\n';
		number_normalize+= 0.1;
	}
	R2file.close();
	*/
/*
	int i = 1;

	path2 = "C:/Users/jonghyeon/Desktop/Data_5/mtp_speed" + to_string(i) + ".csv";
	R2file.open(path2, ios::out);

	path = "C:/Users/jonghyeon/Desktop/Data_5/" + to_string(i) + "/MTP_0.csv";
	checkfile1.open(path, ios::in);
	getline(checkfile1, line);
	getline(checkfile1, line);

	int j = 1;

	float dx8;
	float dy8;
	std::vector< float > speed;
	std::vector< float > speed_normalize;
	
	float mouse_speed;



	while (j < 187900) {

		getline(checkfile1, line);
		vector<string> result1 = split(line, ',');

		
		dx8 = stof(result1[12]);
		dy8 = stof(result1[11]);
		mouse_speed = sqrt(dx8 * dx8 + dy8 * dy8);

	if (stoi(result1[3]) != 1) {
		if (mouse_speed > 0) {
			speed.push_back(mouse_speed);
		}

	}
	j++;
}

	float maximum = *max_element(speed.begin(), speed.end());
	float minimum = *min_element(speed.begin(), speed.end());


	for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) {
		R2file << (speed[speed_counter] - minimum) / (maximum - minimum) << '\n';
	}


	checkfile1.close();
	R2file.close();*/
}	
	




	

	





/// 문제점: Tick을 Base로 해서 돌아버리니까 해결이 안됨. 쭉~ Recoding 해야하는데 이게 안된다는게 문제인거 같음. 한별에게 물어보기?
/// 문제점3 : Optim lib과 충돌하는 문제를 어떻게 해결해야 할까 문제임. 

// Called every frame
void AST_PointActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	if (PeekMessage(&msg, hWnd, 0, 0, PM_QS_INPUT))
	{
		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			throw std::runtime_error("GetRawInputData does not return correct size !\n");
		RAWINPUT* raw = (RAWINPUT*)(lpb);
		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
			
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("(dobby is free)"));
	}
	*/


	/*

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
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	else
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);		
	}*/
	
	end_time = GetWorld()->GetTimeSeconds();
	if (end_time - start_time > 0.015f && counter < 2) {
		
		/*
		int left = 0;
		int right = 0;
		float speed = 0;
		if (click == 5) { right = 1; left = 1; }
		else if (click == 1) { left = 1; }
		else if (click == 4) { right = 1; }

		POINT pt;
		GetCursorPos(&pt);
		
		speed = sqrt((cur_mouse_X2 - pt.x) * (cur_mouse_X2 - pt.x) + (cur_mouse_Y2 - pt.y) * (cur_mouse_Y2 - pt.y)) / (1000 * (result_time2 + end_time - start_time));
		speedset.push_back(speed);
		
		string L = string_format("%f,%d,%d,%d,%d,%d,%d", end_time - start_time, dx, dy, left, right, pt.x, pt.y);

		base2 = base1;
		base1 = L + base;

		result_time2 = result_time1;
		result_time1 = end_time - start_time;
		cur_mouse_X2 = cur_mouse_X;
		cur_mouse_Y2 = cur_mouse_Y;
		cur_mouse_X = pt.x;
		cur_mouse_Y = pt.y;
		dx = 0;
		dy = 0;
		click = 0;
		*/

		start_time = GetWorld()->GetTimeSeconds();
		counter++;
	}

	if (end_time - start_time > 0.015f && counter >= 2) {

		/*

		int left = 0;
		int right = 0;
		float speed = 0;
		
		if (click == 5) { right = 1; left = 1; }
		else if (click == 1) { left = 1; }
		else if (click == 4) { right = 1; }

		POINT pt;
		GetCursorPos(&pt);

		speed = sqrt((cur_mouse_X2 - pt.x) * (cur_mouse_X2 - pt.x) + (cur_mouse_Y2 - pt.y) * (cur_mouse_Y2 - pt.y)) / ((result_time2 + end_time - start_time) * 1000);
		speedset.push_back(speed);

		float value_speed = 0;
		float kernel_sum = 0;

		for (int k = -2; k < 3; k++)
		{
			if ((counter + k) >= 0 && (counter + k) < speedset.size())
			{
				value_speed += speedset[counter + k] * kernel[k + 2];
				kernel_sum += kernel[k + 2];
			}
		}
		filtered_speed = (value_speed / kernel_sum);

		string L = string_format("%f,%d,%d,%d,%d,%d,%d", end_time - start_time, dx, dy, left, right, pt.x, pt.y);

		base2 = base2 + to_string(filtered_speed) + "\n";
		output_file << base2;

		base2 = base1;
		base1 = L + base;

		result_time2 = result_time1;
		result_time1 = end_time - start_time;

		cur_mouse_X2 = cur_mouse_X;
		cur_mouse_Y2 = cur_mouse_Y;
		cur_mouse_X = pt.x;
		cur_mouse_Y = pt.y;
		dx = 0;
		dy = 0;
		click = 0;*/
		start_time = GetWorld()->GetTimeSeconds();
		counter++;
		dx = 0;
		dy = 0;
		//UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
	}

	
}


void AST_PointActor2::QuitLogging() {

	//delete input;
	//delete output;
	//delete func;
	GameOn = false;
	//output_file.close();
	//UnHook();
}/*

void AST_PointActor2::SetHook()
{
	g_hModule = GetModuleHandle(NULL);
	g_hModule2 = GetModuleHandle(NULL);
	if (NULL != g_hModule) {
		g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, g_hModule, NULL);
	}
	if (NULL != g_hModule2) {
		g_hMouse = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_hModule2, 0);
	}
}


void AST_PointActor2::UnHook()
{
	BOOL bKeyboardUnHook = UnhookWindowsHookEx(g_hKeyboard);
	if ((TRUE == bKeyboardUnHook)) {
		g_hKeyboard = NULL;
		FreeLibrary(g_hModule);
		g_hModule = NULL;
	}
	BOOL bMouseUnHook = UnhookWindowsHookEx(g_hMouse);
	if ((TRUE == bMouseUnHook)) {
		g_hMouse = NULL;
		FreeLibrary(g_hModule2);
		g_hModule2 = NULL;
	}
}

LRESULT CALLBACK AST_PointActor2::GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam) {
	dx += 1;
	MSG* msg = (MSG*)lParam;
	GetMessage(msg, NULL, 0, 0);
	switch (msg->message)
	{
	default:
		TranslateMessage(msg);
		DispatchMessage(msg);
		break;


	case WM_INPUT:

		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(msg->lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		RAWINPUT* raw = (RAWINPUT*)(lpb);

		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			dy += int(raw->data.mouse.lLastY);
		}

		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg->lParam);		
		break;
	}
	return CallNextHookEx(g_hHook2, nCode, wParam, lParam);
}

LRESULT CALLBACK AST_PointActor2::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	KBDLLHOOKSTRUCT* keyboard_param = (KBDLLHOOKSTRUCT*)lParam;
	if (keyboard_param->scanCode <= 88) {
		switch (wParam)
		{
		case WM_SYSKEYDOWN:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "1");
			dx += 1;
			break;

		case WM_SYSCHAR:
			dx += 1;
			break;

		case WM_SYSKEYUP:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "0");
			dx += 1;
			break;

		case WM_KEYDOWN:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "1");
			dx += 1;
			break;

		case WM_KEYUP:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "0");
			dx += 1;
			break;

		case WM_CHAR:
			dx += 1;
			break;
		}

	}
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}*/

/*
LRESULT AST_PointActor2::WindowProc(MSG msg, WPARAM wParam, LPARAM lParam) {

	if(msg == WM_INPUT) {
		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			throw std::runtime_error("GetRawInputData does not return correct size !\n");
		RAWINPUT* raw = (RAWINPUT*)(lpb);
		//std::cout << raw->data.keyboard.Reserved << std::endl;
		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	
	return AST_PointActor2::WindowProc(msg, wParam, lParam);
}

/*
void AST_PointActor2::
(void*, float Dx,float Dy) {

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
			dx += raw->data.mouse.lLastX;
			dy += raw->data.mouse.lLastY;
			UE_LOG(LogTemp, Log, TEXT("%f"), dx);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("(%f, %f)"), dx, dy);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}*/



/*
void AST_PointActor2::BindToInput() {

		InputComponent = NewObject<UInputComponent>(this);
		InputComponent->RegisterComponent();
		if (InputComponent)
		{
			InputComponent->BindAction("MoseMoved", IE_Pressed, this, &AST_PointActor2::MouseMoved);
			EnableInput(GetWorld()->GetFirstPlayerController());
		}
	}

void AST_PointActor2::MouseMoved() {

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
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	else
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}
*/
/*
class FMyWindowsMessageHandler
	: public IWindowsMessageHandler
{
public:
	virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) override
	{
		if (msg == WM_INPUT) {
		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (GetRawInputData((HRAWINPUT)(lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			throw std::runtime_error("GetRawInputData does not return correct size !\n");
		RAWINPUT* raw = (RAWINPUT*)(lpb);
		//std::cout << raw->data.keyboard.Reserved << std::endl;
		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	}


}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//메인게임 클래스 내부의 메인 프로시저를 실행시킴

}
*/
/*
void AST_PointActor2::LoggingStart() {

	(new FAutoDeleteAsyncTask<MouseLoggingTask>())->StartBackgroundTask();
}

//------------------------------------------------------------------------------


MouseLoggingTask::MouseLoggingTask() {
	UE_LOG(LogTemp, Log, TEXT("Start"));
}



MouseLoggingTask::~MouseLoggingTask() {
	UE_LOG(LogTemp, Log, TEXT("End"));
}


void MouseLoggingTask::DoWork() {

	dx = 0;
	dy = 0;

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

	while (GameOn) {

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
				dx += raw->data.mouse.lLastX;
				dy += raw->data.mouse.lLastY;
				UE_LOG(LogTemp, Log, TEXT("%f"), dx);
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
/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ST_PointActor2.h"

#include "../../ThirdParty/pointing/pointing.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <Lmcons.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string.h>
#include <io.h>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <tchar.h>  
//#include "optimizer1.h"

#include "persistence1d.hpp"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"

using namespace std;
using namespace p1d;

//using namespace p1d;
//using namespace pointing;

//TransferFunction* func = 0;

ofstream R2file;
ifstream checkfile;
ifstream checkfile1;
ifstream checkfile2;


/*
static HMODULE g_hModule;
static HMODULE g_hModule2;
static HHOOK g_hKeyboard;
static HHOOK g_hMouse;
static HHOOK g_hHook;
static HHOOK g_hHook2;
*/

float dx = 0;
float dy = 0;
bool GameOn = true;

/*
WNDCLASSEX wx;
HWND hWnd;
RAWINPUTDEVICE Rid[2];
*/
//int click = 0;


string path = "C:/Users/jonghyeon/Desktop/Data_5/1/Reaction_0.csv";
// paaaaaaaaaaaaaaaaaaaaaaaaa
string path2 = "C:/Users/jonghyeon/Desktop/Data_5/Reaction_R2/reaction_R2_1.csv";

vector<string> split(string str, char delimiter);

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		answer.push_back(temp);
	}

	return answer;
}

/*
string base = ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,";
string base1 = "";
string base2 = "";
*/
// Sets default values
AST_PointActor2::AST_PointActor2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//result_time2 = 0;
	//result_time1 = 0;
	//counter = 0;	

}
/*
template<typename ... Args> string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
*/
/*
void pointingCallback1(void*, TimeStamp::inttime timestamp, int input_dx, int input_dy, int buttons) {
	int output_dx = 0, output_dy = 0;

	func->applyi(input_dx, input_dy, &output_dx, &output_dy, timestamp);

	dx += input_dx;
	dy += input_dy;
	click = buttons;
}
*/
/*
const string TCHAR_TO_STRING(const TCHAR* a) {
	int len = wcslen((wchar_t*)a);
	char* b = new char[2 * len + 1];
	wcstombs(b, (wchar_t*)a, 2 * len + 1);
	string s = b;
	delete[] b;
	return s;
}
*/

// Called when the game starts or when spawned
void AST_PointActor2::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	
	string line;

	/*
	speedset.push_back(0);
	speedset.push_back(0);
	
	POINT pt;
	GetCursorPos(&pt);

	cur_mouse_X = pt.x;
	cur_mouse_Y = pt.y;
	cur_mouse_X2 = pt.x;
	cur_mouse_Y2 = pt.y;

	input = PointingDevice::create("any:?debugLevel=1");
	output = DisplayDevice::create("any:?debugLevel=1");
	func = TransferFunction::create("sigmoid:?debugLevel=2", input, output);	
	input->setPointingCallback(pointingCallback1);	
	*/


	/*
	TCHAR username[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)username, &size);
	string usernameString = TCHAR_TO_STRING(username);
	string path = "C:/Users/" + usernameString +"/Desktop/Logging.csv";
	output_file.open(path, std::ios::out | std::ios::binary);
	output_file << "Timestamp,dx,dy,leftclick,rightclick, cursor_x,cursor_y,Esc,1,2,3,4,5,6,7,8,9,0,-,=,backspace,tab,Q,W,E,R,T,Y,U,I,O,P,[,],Enter,Ctrl,A,S,D,F,G,H,J,K,L,;,',Lshift,`,\\,Z,X,C,V,B,N,M,comma,.,/,Rshift,PrtSc,Alt,Space,Caps,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NumLock,ScrollLock,Home,Up,PgUp,-,Left,Center,Right,+,End,Down,PgDn,Ins,Del,84,85,86,F11,F12,speed\n";
	start_time = GetWorld()->GetTimeSeconds();
	LoggingStart();
	*/
	//BindToInput();

	//SetHook();	
	/*
	
	float n1 = 0.0f;
	float n2 = 0.0f;
	float n3 = 0.0f;
	//6 con 5 round
	// paaaaaaaaaaaaaaaaaaaaaaaaa
	int num_light =0;

	path2 = "C:/Users/jonghyeon/Desktop/Data_5/Reaction_R2/DD_R2_ToTal.csv";
	R2file.open(path2, ios::out);
	int i = 1;
	int k;
	while (i < 6) {		
		
		int j = 1;
		while (j < 101) {
			path = "C:/Users/jonghyeon/Desktop/Data_5/"+to_string(i)+ "/Reaction_0.csv";
			checkfile.open(path, ios::in);
			getline(checkfile, line);
			D.clear();

			k = 0;
			while (k < 3) {
				int p = j;
				int q = 100 - j;

				while (p > 0) {
					getline(checkfile, line);
					vector<string> result = split(line, ',');

					DD::DATA d;
					d.RT = stof(result[8]);
					d.COR = stoi(result[5]);
					D.load_data(d);
					p--;
				
				}

				while (q > 0) {
					getline(checkfile, line);
					q--;
				}
				
				k++;
								
			}	
			string a = DRIFT_DIFFUSION_MODEL::runOptimizer();
			UE_LOG(LogTemp, Log, TEXT("(dobby is free)"));
			R2file << a ;

			checkfile.close();
			j++;		
		}
		i++;
	}

	R2file.close();
	*/
	


	/*
	
	DD::DATA d;
	d.RT = react_time;
	d.COR = isCorrect;
	D.load_data(d);


	HC::DATA d;
	d.N = num_lamp;
	d.RT = (total_react_time / num_trial);
	H.load_data(d);
	
	string a = HICKS_LAW::runOptimizer();
	while (i <6) {

		n1 = 0.0f;
		n2 = 0.0f;

		HC::DATA d;
		int f = 0;
		int c1 = 0;
		
		int c2 = 16;


		while (f < 16) {

			getline(checkfile, line);
			vector<string> result = split(line, ',');				
			
			n1 = stof(result[0]);

			if (c1 < c2) { n2 += stof(result[1]);}	
			c1++;
			f++;
		
		}
		d.ID = n1;
		d.MT = n2 / float(c2);

		F.load_data(d);
		
		if (stof(result[18]) != 0) {

			n1 = stof(result[18]);
			n2 = stof(result[6]);
			string a3;

			if (n2 > 6.33) { a3 = '1'; }
			else if (n2 > 5.35) {
				if (stof(result[4]) > 15) { a3 = '2'; }
				else { a3 = '3'; }}
			else if (n2 > 4.79) { a3 = '4'; }
			else if (n2 > 4.39) { a3 = '5'; }
			else { a3 = '6'; }


			string a1 = to_string(n2);
			string a2 = to_string(n1);

			R2file << a1 << "," << a2 << "," << a3 << "\n";
		}
		//if (stof(result[5]) > 0.1) { n3++; }

		//float q1 = n1 / float(n2);
		//float q2 = n3 / float(n2);
		
		//if (n2 == 100) {n1 = 0; n2 = 0; n3 = 0;	}
	
		
		i++;
				
	}
	string a = HICKS_LAW::runOptimizer();
	*/
/*
	float n1 = 0.0f;
	float n2 = 0.0f;
	float n3 = 0.0f;
	float n4 = 0.0f;
	float n5 = 0.0f;
	float n6 = 0.0f;

	float e1 = 0.0f;
	float e2 = 0.0f;
	float e3 = 0.0f;
	float e4 = 0.0f;
	float e5 = 0.0f;
	float e6 = 0.0f;
	int i = 3;
	//조건 끝까지{}
	path2 = "C:/Users/jonghyeon/Desktop/Data_5/stp_ER2/R2_" + to_string(i) + ".csv";
	R2file.open(path2, ios::out);

	path = path2 = "C:/Users/jonghyeon/Desktop/Data_5/stp_ER2/ER2_" + to_string(i) + ".csv";
	checkfile1.open(path, ios::in);
	path = "C:/Users/jonghyeon/Desktop/Data_5/stp_ER2/ft_" + to_string(i) + ".csv";
	checkfile2.open(path, ios::in);

	int j = 0;

	while (j < 80) {
		j++;

		getline(checkfile1, line);
		vector<string> result1 = split(line, ',');

		getline(checkfile2, line);
		vector<string> result2 = split(line, ',');


		n1 += stof(result2[1]);
		n2 += stof(result2[3]);
		n3 += stof(result2[5]);
		n4 += stof(result2[7]);
		n5 += stof(result2[9]);
		n6 += stof(result2[11]);
		e1 = stof(result1[0]);
		e2 = stof(result1[1]);
		e3 = stof(result1[2]);
		e4 = stof(result1[3]);
		e5 = stof(result1[4]);
		e6 = stof(result1[5]);

		FT::DATA d;
		d.ID = e1 * stof(result2[0]);
		d.MT = n1 / float(j);

		F.load_data(d);

		FT::DATA d2;
		d2.ID = e2 * stof(result2[2]);
		d2.MT = n2 / float(j);

		F.load_data(d2);

		FT::DATA d3;
		d3.ID = e4 * stof(result2[6]);
		d3.MT = n4 / float(j);
		F.load_data(d3);


		FT::DATA d4;
		d4.ID = e5 * stof(result2[8]);
		d4.MT = n5 / float(j);

		F.load_data(d4);

		FT::DATA d5;
		d5.ID = e6 * stof(result2[10]);
		d5.MT = n6 / float(j);
		F.load_data(d5);


		string cv = FITTS_LAW::runOptimizer();
		R2file << cv;
		F.clear();
	}

	R2file.close();
	checkfile1.close();
	checkfile2.close();
*/
/*
	float number_normalize = 0.0001;
	int i = 5;
	
	path2 ="C:/Users/jonghyeon/Desktop/Data_5/mtp"+to_string(number_normalize) +".csv";
	R2file.open(path2, ios::out);

	path ="C:/Users/jonghyeon/Desktop/Data_5/"+to_string(i)+"/MTP_0.csv";
	checkfile1.open(path, ios::in);
	getline(checkfile1, line);

	int j = 1;
	float time_before = 0;
	float time_now = 0;
	int next_click = 0;
	float tct_Total = 0;

	std::vector< float > speed;
	std::vector< float > speed_normalize;
	std::vector<int> min;
	float dx8=0;
	float dy8=0;
	float mouse_speed;
	float ns=0;
	float fi=0;
	bool flag;
	float Stoic =0;


	while (j < 114905) {	

		getline(checkfile1, line);
		vector<string> result1 = split(line, ',');

		time_now = stof(result1[1]);
		dx8 = stof(result1[12]);
		dy8 = stof(result1[11]);
		mouse_speed = sqrt(dx8 * dx8 + dy8 * dy8);
		
		if (stoi(result1[3]) != 1) {
			if (mouse_speed > 0) {
				speed.push_back(mouse_speed);
				tct_Total += time_now - time_before;
			}
			
		}
		time_before = time_now;
		j++;
	}

	float maximum = *max_element(speed.begin(), speed.end());
	float minimum = *min_element(speed.begin(), speed.end());


	for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) { 
	speed_normalize.push_back((speed[speed_counter] - minimum) / (maximum - minimum));	
	}

	Persistence1D p;
	p.RunPersistence(speed_normalize);

	vector< TPairedExtrema > Extrema;
	p.GetPairedExtrema(Extrema, number_normalize);

	for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
	{
		//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
		min.push_back((*it).MinIndex);
	}


	//std::sort(min.begin(), min.end());

	//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
	//}
	//
	// number of submovement
	UE_LOG(LogTemp, Log, TEXT("%d"), min.size());
	UE_LOG(LogTemp, Log, TEXT("%d"), min.size());
	ns += min.size();

	flag = true;
	Stoic = 0;
	bool positive = true;
	float before = 0;

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
	UE_LOG(LogTemp, Log, TEXT("%f"), tct_Total);
	ns = ns / tct_Total;
	fi = fi / tct_Total;

	R2file << number_normalize<< ',' << ns << ',' << fi << ',' << min.size() << ',' << speed_normalize.size() << '\n';
	checkfile1.close();



	

	while (number_normalize < 1) {
		number_normalize += 0.0001;
		min = {};
		ns = 0;
		fi = 0;
		Extrema = {};

		p.RunPersistence(speed_normalize);
		p.GetPairedExtrema(Extrema, number_normalize);

		for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min.push_back((*it).MinIndex);
		}


		//std::sort(min.begin(), min.end());

		//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
		//}
		//
		// number of submovement
		ns += min.size();

		flag = true;
		Stoic = 0;
		positive = true;
		before = 0;

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
		ns = ns / tct_Total;
		fi = fi / tct_Total;

		R2file << number_normalize << ',' << ns << ',' << fi << ',' << min.size() << ',' << speed_normalize.size() << '\n';
	}
	R2file.close();


	number_normalize = 0.1;
	path2 = "C:/Users/jonghyeon/Desktop/Data_5/mtp" + to_string(number_normalize) + ".csv";
	R2file.open(path2, ios::out);


	while (number_normalize < 100) {
		
		min = {};
		ns = 0;
		fi = 0;
		Extrema = {};

		p.RunPersistence(speed);
		p.GetPairedExtrema(Extrema, number_normalize);

		for (vector< TPairedExtrema >::iterator it = Extrema.begin(); it != Extrema.end(); it++)
		{
			//UE_LOG(LogTemp, Log, TEXT("persistence: %f , MinIndex: %d, MaxIndex: %d"), (*it).Persistence , (*it).MinIndex, (*it).MaxIndex);	
			min.push_back((*it).MinIndex);
		}


		//std::sort(min.begin(), min.end());

		//for (vector< int >::iterator it = min.begin(); it != min.end(); it++)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("indices: %d"), (*it));
		//}
		//
		// number of submovement
		ns += min.size();

		flag = true;
		Stoic = 0;
		positive = true;
		before = 0;

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
		ns = ns / tct_Total;
		fi = fi / tct_Total;

		R2file << number_normalize << ',' << ns << ',' << fi << ',' << min.size() << ',' << speed_normalize.size() << '\n';
		number_normalize+= 0.1;
	}
	R2file.close();
	*/
/*
	int i = 1;

	path2 = "C:/Users/jonghyeon/Desktop/Data_5/mtp_speed" + to_string(i) + ".csv";
	R2file.open(path2, ios::out);

	path = "C:/Users/jonghyeon/Desktop/Data_5/" + to_string(i) + "/MTP_0.csv";
	checkfile1.open(path, ios::in);
	getline(checkfile1, line);
	getline(checkfile1, line);

	int j = 1;

	float dx8;
	float dy8;
	std::vector< float > speed;
	std::vector< float > speed_normalize;
	
	float mouse_speed;



	while (j < 187900) {

		getline(checkfile1, line);
		vector<string> result1 = split(line, ',');

		
		dx8 = stof(result1[12]);
		dy8 = stof(result1[11]);
		mouse_speed = sqrt(dx8 * dx8 + dy8 * dy8);

	if (stoi(result1[3]) != 1) {
		if (mouse_speed > 0) {
			speed.push_back(mouse_speed);
		}

	}
	j++;
}

	float maximum = *max_element(speed.begin(), speed.end());
	float minimum = *min_element(speed.begin(), speed.end());


	for (int speed_counter = 0; speed_counter < speed.size(); speed_counter++) {
		R2file << (speed[speed_counter] - minimum) / (maximum - minimum) << '\n';
	}


	checkfile1.close();
	R2file.close();*/
}	
	




	

	





/// 문제점: Tick을 Base로 해서 돌아버리니까 해결이 안됨. 쭉~ Recoding 해야하는데 이게 안된다는게 문제인거 같음. 한별에게 물어보기?
/// 문제점3 : Optim lib과 충돌하는 문제를 어떻게 해결해야 할까 문제임. 

// Called every frame
void AST_PointActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	if (PeekMessage(&msg, hWnd, 0, 0, PM_QS_INPUT))
	{
		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			throw std::runtime_error("GetRawInputData does not return correct size !\n");
		RAWINPUT* raw = (RAWINPUT*)(lpb);
		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
			
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("(dobby is free)"));
	}
	*/


	/*

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
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	else
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);		
	}*/
	
	end_time = GetWorld()->GetTimeSeconds();
	if (end_time - start_time > 0.015f && counter < 2) {
		
		/*
		int left = 0;
		int right = 0;
		float speed = 0;
		if (click == 5) { right = 1; left = 1; }
		else if (click == 1) { left = 1; }
		else if (click == 4) { right = 1; }

		POINT pt;
		GetCursorPos(&pt);
		
		speed = sqrt((cur_mouse_X2 - pt.x) * (cur_mouse_X2 - pt.x) + (cur_mouse_Y2 - pt.y) * (cur_mouse_Y2 - pt.y)) / (1000 * (result_time2 + end_time - start_time));
		speedset.push_back(speed);
		
		string L = string_format("%f,%d,%d,%d,%d,%d,%d", end_time - start_time, dx, dy, left, right, pt.x, pt.y);

		base2 = base1;
		base1 = L + base;

		result_time2 = result_time1;
		result_time1 = end_time - start_time;
		cur_mouse_X2 = cur_mouse_X;
		cur_mouse_Y2 = cur_mouse_Y;
		cur_mouse_X = pt.x;
		cur_mouse_Y = pt.y;
		dx = 0;
		dy = 0;
		click = 0;
		*/

		start_time = GetWorld()->GetTimeSeconds();
		counter++;
	}

	if (end_time - start_time > 0.015f && counter >= 2) {

		/*

		int left = 0;
		int right = 0;
		float speed = 0;
		
		if (click == 5) { right = 1; left = 1; }
		else if (click == 1) { left = 1; }
		else if (click == 4) { right = 1; }

		POINT pt;
		GetCursorPos(&pt);

		speed = sqrt((cur_mouse_X2 - pt.x) * (cur_mouse_X2 - pt.x) + (cur_mouse_Y2 - pt.y) * (cur_mouse_Y2 - pt.y)) / ((result_time2 + end_time - start_time) * 1000);
		speedset.push_back(speed);

		float value_speed = 0;
		float kernel_sum = 0;

		for (int k = -2; k < 3; k++)
		{
			if ((counter + k) >= 0 && (counter + k) < speedset.size())
			{
				value_speed += speedset[counter + k] * kernel[k + 2];
				kernel_sum += kernel[k + 2];
			}
		}
		filtered_speed = (value_speed / kernel_sum);

		string L = string_format("%f,%d,%d,%d,%d,%d,%d", end_time - start_time, dx, dy, left, right, pt.x, pt.y);

		base2 = base2 + to_string(filtered_speed) + "\n";
		output_file << base2;

		base2 = base1;
		base1 = L + base;

		result_time2 = result_time1;
		result_time1 = end_time - start_time;

		cur_mouse_X2 = cur_mouse_X;
		cur_mouse_Y2 = cur_mouse_Y;
		cur_mouse_X = pt.x;
		cur_mouse_Y = pt.y;
		dx = 0;
		dy = 0;
		click = 0;*/
		start_time = GetWorld()->GetTimeSeconds();
		counter++;
		dx = 0;
		dy = 0;
		//UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
	}

	
}


void AST_PointActor2::QuitLogging() {

	//delete input;
	//delete output;
	//delete func;
	GameOn = false;
	//output_file.close();
	//UnHook();
}/*

void AST_PointActor2::SetHook()
{
	g_hModule = GetModuleHandle(NULL);
	g_hModule2 = GetModuleHandle(NULL);
	if (NULL != g_hModule) {
		g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, g_hModule, NULL);
	}
	if (NULL != g_hModule2) {
		g_hMouse = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_hModule2, 0);
	}
}


void AST_PointActor2::UnHook()
{
	BOOL bKeyboardUnHook = UnhookWindowsHookEx(g_hKeyboard);
	if ((TRUE == bKeyboardUnHook)) {
		g_hKeyboard = NULL;
		FreeLibrary(g_hModule);
		g_hModule = NULL;
	}
	BOOL bMouseUnHook = UnhookWindowsHookEx(g_hMouse);
	if ((TRUE == bMouseUnHook)) {
		g_hMouse = NULL;
		FreeLibrary(g_hModule2);
		g_hModule2 = NULL;
	}
}

LRESULT CALLBACK AST_PointActor2::GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam) {
	dx += 1;
	MSG* msg = (MSG*)lParam;
	GetMessage(msg, NULL, 0, 0);
	switch (msg->message)
	{
	default:
		TranslateMessage(msg);
		DispatchMessage(msg);
		break;


	case WM_INPUT:

		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(msg->lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		RAWINPUT* raw = (RAWINPUT*)(lpb);

		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			dy += int(raw->data.mouse.lLastY);
		}

		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg->lParam);		
		break;
	}
	return CallNextHookEx(g_hHook2, nCode, wParam, lParam);
}

LRESULT CALLBACK AST_PointActor2::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	KBDLLHOOKSTRUCT* keyboard_param = (KBDLLHOOKSTRUCT*)lParam;
	if (keyboard_param->scanCode <= 88) {
		switch (wParam)
		{
		case WM_SYSKEYDOWN:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "1");
			dx += 1;
			break;

		case WM_SYSCHAR:
			dx += 1;
			break;

		case WM_SYSKEYUP:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "0");
			dx += 1;
			break;

		case WM_KEYDOWN:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "1");
			dx += 1;
			break;

		case WM_KEYUP:
			base.replace(keyboard_param->scanCode * 2 - 1, 1, "0");
			dx += 1;
			break;

		case WM_CHAR:
			dx += 1;
			break;
		}

	}
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}*/

/*
LRESULT AST_PointActor2::WindowProc(MSG msg, WPARAM wParam, LPARAM lParam) {

	if(msg == WM_INPUT) {
		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (GetRawInputData((HRAWINPUT)(msg.lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			throw std::runtime_error("GetRawInputData does not return correct size !\n");
		RAWINPUT* raw = (RAWINPUT*)(lpb);
		//std::cout << raw->data.keyboard.Reserved << std::endl;
		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	
	return AST_PointActor2::WindowProc(msg, wParam, lParam);
}

/*
void AST_PointActor2::
(void*, float Dx,float Dy) {

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
			dx += raw->data.mouse.lLastX;
			dy += raw->data.mouse.lLastY;
			UE_LOG(LogTemp, Log, TEXT("%f"), dx);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("(%f, %f)"), dx, dy);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}*/



/*
void AST_PointActor2::BindToInput() {

		InputComponent = NewObject<UInputComponent>(this);
		InputComponent->RegisterComponent();
		if (InputComponent)
		{
			InputComponent->BindAction("MoseMoved", IE_Pressed, this, &AST_PointActor2::MouseMoved);
			EnableInput(GetWorld()->GetFirstPlayerController());
		}
	}

void AST_PointActor2::MouseMoved() {

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
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	else
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}
*/
/*
class FMyWindowsMessageHandler
	: public IWindowsMessageHandler
{
public:
	virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) override
	{
		if (msg == WM_INPUT) {
		UINT dwSize = 0;
		GetRawInputData((HRAWINPUT)(lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (GetRawInputData((HRAWINPUT)(lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			throw std::runtime_error("GetRawInputData does not return correct size !\n");
		RAWINPUT* raw = (RAWINPUT*)(lpb);
		//std::cout << raw->data.keyboard.Reserved << std::endl;
		if (raw->header.dwType == RIM_TYPEMOUSE) {
			dx += int(raw->data.mouse.lLastX);
			UE_LOG(LogTemp, Log, TEXT("(%f)"), dx);
			dy += int(raw->data.mouse.lLastY);
		}
		else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
		}
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(lParam);
		// retrieve and process data from hRawInput as needed...
		//std::cout << msg.pt.x << std::endl;
	}
	}


}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//메인게임 클래스 내부의 메인 프로시저를 실행시킴

}
*/
/*
void AST_PointActor2::LoggingStart() {

	(new FAutoDeleteAsyncTask<MouseLoggingTask>())->StartBackgroundTask();
}

//------------------------------------------------------------------------------


MouseLoggingTask::MouseLoggingTask() {
	UE_LOG(LogTemp, Log, TEXT("Start"));
}



MouseLoggingTask::~MouseLoggingTask() {
	UE_LOG(LogTemp, Log, TEXT("End"));
}


void MouseLoggingTask::DoWork() {

	dx = 0;
	dy = 0;

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

	while (GameOn) {

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
				dx += raw->data.mouse.lLastX;
				dy += raw->data.mouse.lLastY;
				UE_LOG(LogTemp, Log, TEXT("%f"), dx);
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
}*/