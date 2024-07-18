<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.




#include "FloatingActor.h"

#include "optimizer.h"
#include <time.h>
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include <Engine/Classes/Components/TextRenderComponent.h>


ofstream output_file1;
ifstream checker_file1;

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	key_set = { EKeys::One, EKeys::Two, EKeys::Three, EKeys::Four};
	num_lamp_index = {1,2,4};
	FRandomStream Stream(FMath::Rand());

	
	stop = false;
	Big_Trial = 0;
	num_Big_Trial = 3;
	num_trial = 80;
	trial = 0;
	randint = 0;
	interval = -200;
	colored = false;
	pressed = false;
	need_change_color = true;
	file_opened = false;
	write_to_file = false;
	total_react_time = 0;
	correctTotal = 0;
}

	
// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	Set2DView(); 

	int tmp_lamp=0;
	int tmp_button=0;

	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Cube")) Buttons.Add(Actor);
		else if (Actor->GetName().Contains("Sphere")) Lamps.Add(Actor);
	}

	num_lamp = num_lamp_index[Big_Trial];

	string path;
	int i = 0;
	bool fileopen = false;

	while (!fileopen) {

		path = "../../../Log/Reaction_" + to_string(i) + ".csv";

		checker_file1.open(path);
		if (!checker_file1.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file1.close();
	}



	output_file1.open(path, std::ios::out | std::ios::binary);
	output_file1 << "UserID,NumLight,Trial,Colored,Pressed,Correct,trialStartTime,PressedTime,ReactionTime\n";

	time_t seconds;
	seconds = time(NULL);
	srand(seconds);
	for (int32 k = 8; k > 0; k--) {		
		int32 j = int(rand()) % num_lamp_index.Num();
		int temp = num_lamp_index[k % num_lamp_index.Num()];
		num_lamp_index[k % num_lamp_index.Num()] = num_lamp_index[j];
		num_lamp_index[j] = temp;
	}
	UE_LOG(LogTemp, Log, TEXT("%d,%d,%d"), num_lamp_index[0], num_lamp_index[1], num_lamp_index[2]);
	///for (int i = 7; i >= num_lamp ; i--) {
	///	Lamps[i]->Destroy();
	///	Buttons[i]->Destroy();
	///}

}



// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("colored :: %d"),colored);
	
	if (write_to_file) {

		string L = "";
		//UE_LOG(LogTemp, Log, TEXT("write"));

		std::string userIDString(TCHAR_TO_UTF8(*userID));
		L = userIDString +"," + string_format("%d,%d,%d,%d,%d,%f,%f,%f", num_lamp, trial, writeColor, num_pressed, writeCorrect,start_time,end_time, react_time) + '\n';
		output_file1 << L;	
	
		write_to_file = false;
	}


	if (trial == 0 && !Locate && Big_Trial < 3) {
		num_lamp = num_lamp_index[Big_Trial];

		if (num_lamp == 1) {
			for (int i = 0; i < num_lamp; i++) {
				Lamps[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3.5), 500));
				Buttons[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3.5), 100));
			}
			for (int i = 7; i >= num_lamp; i--) {
				Lamps[i]->SetActorLocation(FVector(-5000, 5000, 5000));
				Buttons[i]->SetActorLocation(FVector(-5000, 5000, 5000));
			}
			num_trial = 40;
		}

		if (num_lamp == 2) {
			for (int i = 0; i < num_lamp; i++) {
				Lamps[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3), 500));
				Buttons[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3), 100));
			}
			for (int i = 7; i >= num_lamp; i--) {
				Lamps[i]->SetActorLocation(FVector(-5000, 5000, 5000));
				Buttons[i]->SetActorLocation(FVector(-5000, 5000, 5000));
			}
			num_trial = 120;
		}

		if (num_lamp == 4) {
			for (int i = 0; i < num_lamp; i++) {
				Lamps[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+2), 500));
				Buttons[i]->SetActorLocation(FVector(-1250, 600 + interval * (i + 2), 100));
			}
			for (int i = 7; i >= num_lamp; i--) {
				Lamps[i]->SetActorLocation(FVector(-5000, 5000, 5000));
				Buttons[i]->SetActorLocation(FVector(-5000, 5000, 5000));
			}
			num_trial = 80;
		}

				
		BindToInput();
		Big_Trial++;

		Locate = true;
	}

	if (trial == num_trial && Big_Trial != 3 && !stop)
	{

		/*
		HC::DATA d;
		d.N = num_lamp;
		d.RT = (total_react_time / num_trial);

		UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));
		total_react_time = 0;
		H.load_data(d);
		*/

		N.push_back(num_lamp);
		RT.push_back(float(total_react_time / float(num_trial)));
		total_react_time = 0;
		//UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));

		trial = 0;
		Locate = false;
		stop = true;
	}


    if (trial == num_trial && Epressed && Big_Trial == 3)
    {   
		/*
		HC::DATA d;
		d.N = num_lamp;
		d.RT = (total_react_time / num_trial);
		H.load_data(d);
		UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));
		total_react_time = 0;
		*/
		N.push_back(num_lamp);
		RT.push_back(float(total_react_time / float(num_trial)));
		//UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));


		total_react_time = 0;
		GameStarted = false;
		is_PressedE();		
		trial = 0;
    }
	if (!DataSended && GameStarted && !stop) { RepeatingFunc(); }
	

}


void AFloatingActor::GameStart()
{
	GameStarted= true;
}


void AFloatingActor::RepeatingFunc() //불이 꺼져있으면 램프에 불 생성
{
	if (!colored && need_change_color) {
		pressed = false;
		need_change_color = false;
		delay_time = delay();
		GetWorldTimerManager().SetTimer(CountdownTimerHandle2, FTimerDelegate::CreateLambda([&]() //delay time만큼의 delay 후 램프에 불 키기
			{
				int length = num_lamp;
				randint = FMath::RandRange(0, num_lamp - 1);
				UStaticMeshComponent* mesh = Lamps[randint]->FindComponentByClass<UStaticMeshComponent>();
				mesh->CreateDynamicMaterialInstance(0);
				mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 0.0f, 0.0f));
				colored = true;
				start_time = GetWorld()->GetTimeSeconds();
			}), delay_time, false);
	}
}



float AFloatingActor::delay() 
{
	float rand_time = FMath::RandRange(0.3f, 2.0f);
	return rand_time;
}

void AFloatingActor::BindToInput()
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
		if (InputComponent)
		{
			InputComponent->BindKey(key_set[0], IE_Pressed, this, &AFloatingActor::is_Pressed1);
			
			if (num_lamp >= 2) InputComponent->BindKey(key_set[1], IE_Pressed, this, &AFloatingActor::is_Pressed2);
			if (num_lamp >= 4)
			{
				InputComponent->BindKey(key_set[2], IE_Pressed, this, &AFloatingActor::is_Pressed3);
				InputComponent->BindKey(key_set[3], IE_Pressed, this, &AFloatingActor::is_Pressed4);
			}
			/*
			if (num_lamp >= 8) {

				InputComponent->BindKey(key_set[4], IE_Pressed, this, &AFloatingActor::is_Pressed5);
				InputComponent->BindKey(key_set[5], IE_Pressed, this, &AFloatingActor::is_Pressed6);
				InputComponent->BindKey(key_set[6], IE_Pressed, this, &AFloatingActor::is_Pressed7);
				InputComponent->BindKey(key_set[7], IE_Pressed, this, &AFloatingActor::is_Pressed8);
			};*/
			// Now hook up our InputComponent to one in a Player
			// Controller, so that input flows down to us
			EnableInput(GetWorld()->GetFirstPlayerController());
		}
}

void AFloatingActor::is_Pressed1()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 0) { 				
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint+1);
		Press.push_back(1);

		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"),react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;

		if (num_lamp == 2) {
			DD::DATA d;
			d.RT = react_time;
			d.COR = isCorrect;
			D.load_data(d);
			UE_LOG(LogTemp, Log, TEXT("1 in lamp2"));
		}
		
		//(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 1, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);
		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 1;
		writeColor = randint + 1;
		
		coloring();

		
	}
}

void AFloatingActor::is_Pressed2()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 1) {
			
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint+1);
		Press.push_back(2);

    	react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		if (num_lamp == 2) {
			DD::DATA d;
			d.RT = react_time;
			d.COR = isCorrect;
			D.load_data(d);
			UE_LOG(LogTemp, Log, TEXT("2 in lamp2") );
			
		}

		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);
		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 2;
		writeColor = randint + 1;

		coloring();



	}
}

void AFloatingActor::is_Pressed3()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 2){
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint + 1);
		Press.push_back(3);


		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;


		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 3, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);
		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 3;
		writeColor = randint + 1;

		coloring();

	}
}

void AFloatingActor::is_Pressed4()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 3) {
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint + 1);
		Press.push_back(4);

		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;

		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);


		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 4;
		writeColor = randint + 1;

		coloring();

	}
}

/*
void AFloatingActor::is_Pressed5()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 4) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);


		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}


void AFloatingActor::is_Pressed6()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 5) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);


		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}

void AFloatingActor::is_Pressed7()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 6) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);


	//	UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}

void AFloatingActor::is_Pressed8()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 7) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);

//
	//	UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}
*/



void AFloatingActor::is_PressedE(){	
	string a = DRIFT_DIFFUSION_MODEL::runOptimizer();	
	//UE_LOG(LogTemp, Log, TEXT("%s" ),a);

	for (int three = 0; three < num_Big_Trial; three++) {
		HC::DATA d;

		d.N = N[three];
		d.RT =RT[three];
		//UE_LOG(LogTemp, Log, TEXT("%d, %f"), N[three],RT[three]);

				
	
		H.load_data(d);
	}

	string b = HICKS_LAW::runOptimizer();
	H.clear();

	for (int three = 0; three < num_Big_Trial; three++) {
		HC::DATA d;

		d.RT = RT[three];

		int S1 = 0;
		int S2 = 0;
		int S3 = 0;
		int S4 = 0;

		int R1 = 0;
		int R2 = 0;
		int R3 = 0;
		int R4 = 0;
		
		int SR11 = 0;
		int SR12 = 0;
		int SR13 = 0;
		int SR14 = 0;

		int SR21 = 0;
		int SR22 = 0;
		int SR23 = 0;
		int SR24 = 0;

		int SR31 = 0;
		int SR32 = 0;
		int SR33 = 0;
		int SR34 = 0;

		int SR41 = 0;
		int SR42 = 0;
		int SR43 = 0;
		int SR44 = 0;


		for (int hundred = three * num_trial; hundred < three * num_trial + num_trial; hundred++) {

			if (Lit[hundred] == 1) {
				S1++;

				if (Press[hundred] == 1) { R1++;	SR11++; }
				else if (Press[hundred] == 2) { R2++;	SR12++; }
				else if (Press[hundred] == 3) { R3++;	SR13++; }
				else if (Press[hundred] == 4) { R4++;	SR14++; }

			}
			if (Lit[hundred] == 2) {
				S2++;

				if (Press[hundred] == 1) { R1++;	SR21++; }
				else if (Press[hundred] == 2) { R2++;	SR22++; }
				else if (Press[hundred] == 3) { R3++;	SR23++; }
				else if (Press[hundred] == 4) { R4++;	SR24++; }

			}
			if (Lit[hundred] == 3) {
				S3++;

				if (Press[hundred] == 1) { R1++;	SR31++; }
				else if (Press[hundred] == 2) { R2++;	SR32++; }
				else if (Press[hundred] == 3) { R3++;	SR33++; }
				else if (Press[hundred] == 4) { R4++;	SR34++; }

			}
			if (Lit[hundred] == 4) {
				S4++;

				if (Press[hundred] == 1) { R1++;	SR41++; }
				else if (Press[hundred] == 2) { R2++;	SR42++; }
				else if (Press[hundred] == 3) { R3++;	SR43++; }
				else if (Press[hundred] == 4) { R4++;	SR44++; }

			}

		}

		float HS = -log2((1.0f / float(N[three])));
		float HR = 0;
		float HSR = 0;

		if (N[three] == 1) {
			HR = -(float(R1) / 80.0f) * log2(float(R1) / 80.0f);
			HSR = -(float(SR11) / 80.0f) * log2(float(SR11) / 80.0f);
		}
		else if (N[three] == 2) {
			if (R1 != 0) {HR -= (float(R1) / 80.0f) * log2(float(R1) / 80.0f);}
			if (R2 != 0) {HR -= (float(R2) / 80.0f) * log2(float(R2) / 80.0f);}
			if (SR11 != 0) {HSR -= (float(SR11) / 80.0f) * log2(float(SR11) / 80.0f);}
			if (SR12 != 0) {HSR -= (float(SR12) / 80.0f) * log2(float(SR12) / 80.0f);}
			if (SR21 != 0) {HSR -= (float(SR21) / 80.0f) * log2(float(SR21) / 80.0f);}
			if (SR22 != 0) {HSR -= (float(SR22) / 80.0f) * log2(float(SR22) / 80.0f);}
		}
		else if (N[three] == 4) {
			if (R1 != 0) {	HR -= (float(R1) / 80.0f) * log2(float(R1) / 80.0f);}
			if (R2 != 0) {	HR -= (float(R2) / 80.0f) * log2(float(R2) / 80.0f);}
			if (R3 != 0) {	HR -= (float(R3) / 80.0f) * log2(float(R3) / 80.0f);}
			if (R4 != 0) {	HR -= (float(R4) / 80.0f) * log2(float(R4) / 80.0f);}

			if (SR11 != 0) {HSR -= (float(SR11) / 80.0f) * log2(float(SR11) / 80.0f);}
			if (SR12 != 0) {HSR -= (float(SR12) / 80.0f) * log2(float(SR12) / 80.0f);}
			if (SR13 != 0) {HSR -= (float(SR13) / 80.0f) * log2(float(SR13) / 80.0f);}
			if (SR14 != 0) {HSR -= (float(SR14) / 80.0f) * log2(float(SR14) / 80.0f);}
			if (SR21 != 0) {HSR -= (float(SR21) / 80.0f) * log2(float(SR21) / 80.0f);}
			if (SR22 != 0) {HSR -= (float(SR22) / 80.0f) * log2(float(SR22) / 80.0f);}
			if (SR23 != 0) {HSR -= (float(SR23) / 80.0f) * log2(float(SR23) / 80.0f);}
			if (SR24 != 0) {HSR -= (float(SR24) / 80.0f) * log2(float(SR24) / 80.0f);}
			if (SR31 != 0) {HSR -= (float(SR31) / 80.0f) * log2(float(SR31) / 80.0f);}
			if (SR32 != 0) {HSR -= (float(SR32) / 80.0f) * log2(float(SR32) / 80.0f);}
			if (SR33 != 0) {HSR -= (float(SR33) / 80.0f) * log2(float(SR33) / 80.0f);}
			if (SR34 != 0) {HSR -= (float(SR34) / 80.0f) * log2(float(SR34) / 80.0f);}
			if (SR41 != 0) {HSR -= (float(SR41) / 80.0f) * log2(float(SR41) / 80.0f);}
			if (SR42 != 0) {HSR -= (float(SR42) / 80.0f) * log2(float(SR42) / 80.0f);}
			if (SR43 != 0) {HSR -= (float(SR43) / 80.0f) * log2(float(SR43) / 80.0f);}
			if (SR44 != 0) {HSR -= (float(SR44) / 80.0f) * log2(float(SR44) / 80.0f);}
		}

		//UE_LOG(LogTemp, Log, TEXT("%f,%f,%f"), HS, HR, HSR);

		//UE_LOG(LogTemp, Log, TEXT("%d,%d,%d,%d"), R1, R2, R3,R4);
		//UE_LOG(LogTemp, Log, TEXT("%d,%d,%d,%d"), S1, S2, S3, S4);
		//UE_LOG(LogTemp, Log, TEXT("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"), SR11, SR12, SR13, SR14, SR21, SR22, SR23, SR24, SR31, SR32, SR33, SR34, SR41, SR42, SR43, SR44);



		//UE_LOG(LogTemp, Log, TEXT("%d"), N[three]);

		float Nelog2 = HS + HR - HSR;
		//UE_LOG(LogTemp, Log, TEXT("%f"), Nelog2);
		d.N = pow(2,Nelog2);

		//UE_LOG(LogTemp, Log, TEXT("%f,%f"), pow(2, Nelog2) , RT[three]);
		H.load_data(d);
	}
	string c = HICKS_LAW::runOptimizer();

	b = b + ',' + c + string_format(",%f,%f", 1.0f - (float(correctTotal) / 240.0f), (RT[0] + RT[1] + RT[2]) / 3.0f);

	
	ResultData = (a.c_str());
	ResultData2 = (b.c_str());
	UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData);
	UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData2);

	DataSended = true;

	//output_file1.close();
	

}


void AFloatingActor::LocateMaterial(int num_of_cube, TArray<AActor*> Lamp, TArray<AActor*> Button ) {

	for (int i = 0; i < num_of_cube; i++) {
		Lamp[i]->SetActorLocation(FVector(-1250, 600 + interval * i, 500));
		Button[i]->SetActorLocation(FVector(-1250, 600 + interval * i, 100));
	}


	for (int i = 7; i >= num_of_cube; i--) {
		Lamp[i]->SetActorLocation(FVector(-5000, 600 + interval * i, 500));
		Button[i]->SetActorLocation(FVector(-5000, 600 + interval * i, 100));
	}

	BindToInput();
}


void AFloatingActor::coloring()
{
	UStaticMeshComponent* mesh = Lamps[randint]->FindComponentByClass<UStaticMeshComponent>();
	mesh->CreateDynamicMaterialInstance(0);
	mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 1.0f, 1.0f));
	trial++;
	pressed = true;
	colored = false;
	need_change_color = true;
	isCorrect = 0.0f;
}


void AFloatingActor::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
=======
// Fill out your copyright notice in the Description page of Project Settings.




#include "FloatingActor.h"

#include "optimizer.h"
#include <time.h>
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include <Engine/Classes/Components/TextRenderComponent.h>


ofstream output_file1;
ifstream checker_file1;

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	key_set = { EKeys::One, EKeys::Two, EKeys::Three, EKeys::Four};
	num_lamp_index = {1,2,4};
	FRandomStream Stream(FMath::Rand());

	
	stop = false;
	Big_Trial = 0;
	num_Big_Trial = 3;
	num_trial = 80;
	trial = 0;
	randint = 0;
	interval = -200;
	colored = false;
	pressed = false;
	need_change_color = true;
	file_opened = false;
	write_to_file = false;
	total_react_time = 0;
	correctTotal = 0;
}

	
// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> TotalActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), TotalActor);
	SpecificPlayer1 = GetWorld()->GetFirstPlayerController(); //마우스 커서 보이기
	SpecificPlayer1->bShowMouseCursor = true;
	SpecificPlayer1->bEnableClickEvents = true;
	Set2DView(); 

	int tmp_lamp=0;
	int tmp_button=0;

	for (AActor* Actor : TotalActor) {
		if (Actor->GetName().Contains("Cube")) Buttons.Add(Actor);
		else if (Actor->GetName().Contains("Sphere")) Lamps.Add(Actor);
	}

	num_lamp = num_lamp_index[Big_Trial];

	string path;
	int i = 0;
	bool fileopen = false;

	while (!fileopen) {

		path = "../../../Log/Reaction_" + to_string(i) + ".csv";

		checker_file1.open(path);
		if (!checker_file1.is_open()) {
			fileopen = true;
		}
		else { i++; }
		checker_file1.close();
	}



	output_file1.open(path, std::ios::out | std::ios::binary);
	output_file1 << "UserID,NumLight,Trial,Colored,Pressed,Correct,trialStartTime,PressedTime,ReactionTime\n";

	time_t seconds;
	seconds = time(NULL);
	srand(seconds);
	for (int32 k = 8; k > 0; k--) {		
		int32 j = int(rand()) % num_lamp_index.Num();
		int temp = num_lamp_index[k % num_lamp_index.Num()];
		num_lamp_index[k % num_lamp_index.Num()] = num_lamp_index[j];
		num_lamp_index[j] = temp;
	}
	UE_LOG(LogTemp, Log, TEXT("%d,%d,%d"), num_lamp_index[0], num_lamp_index[1], num_lamp_index[2]);
	///for (int i = 7; i >= num_lamp ; i--) {
	///	Lamps[i]->Destroy();
	///	Buttons[i]->Destroy();
	///}

}



// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("colored :: %d"),colored);
	
	if (write_to_file) {

		string L = "";
		//UE_LOG(LogTemp, Log, TEXT("write"));

		std::string userIDString(TCHAR_TO_UTF8(*userID));
		L = userIDString +"," + string_format("%d,%d,%d,%d,%d,%f,%f,%f", num_lamp, trial, writeColor, num_pressed, writeCorrect,start_time,end_time, react_time) + '\n';
		output_file1 << L;	
	
		write_to_file = false;
	}


	if (trial == 0 && !Locate && Big_Trial < 3) {
		num_lamp = num_lamp_index[Big_Trial];

		if (num_lamp == 1) {
			for (int i = 0; i < num_lamp; i++) {
				Lamps[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3.5), 500));
				Buttons[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3.5), 100));
			}
			for (int i = 7; i >= num_lamp; i--) {
				Lamps[i]->SetActorLocation(FVector(-5000, 5000, 5000));
				Buttons[i]->SetActorLocation(FVector(-5000, 5000, 5000));
			}
			num_trial = 40;
		}

		if (num_lamp == 2) {
			for (int i = 0; i < num_lamp; i++) {
				Lamps[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3), 500));
				Buttons[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+3), 100));
			}
			for (int i = 7; i >= num_lamp; i--) {
				Lamps[i]->SetActorLocation(FVector(-5000, 5000, 5000));
				Buttons[i]->SetActorLocation(FVector(-5000, 5000, 5000));
			}
			num_trial = 120;
		}

		if (num_lamp == 4) {
			for (int i = 0; i < num_lamp; i++) {
				Lamps[i]->SetActorLocation(FVector(-1250, 600 + interval * (i+2), 500));
				Buttons[i]->SetActorLocation(FVector(-1250, 600 + interval * (i + 2), 100));
			}
			for (int i = 7; i >= num_lamp; i--) {
				Lamps[i]->SetActorLocation(FVector(-5000, 5000, 5000));
				Buttons[i]->SetActorLocation(FVector(-5000, 5000, 5000));
			}
			num_trial = 80;
		}

				
		BindToInput();
		Big_Trial++;

		Locate = true;
	}

	if (trial == num_trial && Big_Trial != 3 && !stop)
	{

		/*
		HC::DATA d;
		d.N = num_lamp;
		d.RT = (total_react_time / num_trial);

		UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));
		total_react_time = 0;
		H.load_data(d);
		*/

		N.push_back(num_lamp);
		RT.push_back(float(total_react_time / float(num_trial)));
		total_react_time = 0;
		//UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));

		trial = 0;
		Locate = false;
		stop = true;
	}


    if (trial == num_trial && Epressed && Big_Trial == 3)
    {   
		/*
		HC::DATA d;
		d.N = num_lamp;
		d.RT = (total_react_time / num_trial);
		H.load_data(d);
		UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));
		total_react_time = 0;
		*/
		N.push_back(num_lamp);
		RT.push_back(float(total_react_time / float(num_trial)));
		//UE_LOG(LogTemp, Log, TEXT("%d, %f "), num_lamp, (total_react_time / num_trial));


		total_react_time = 0;
		GameStarted = false;
		is_PressedE();		
		trial = 0;
    }
	if (!DataSended && GameStarted && !stop) { RepeatingFunc(); }
	

}


void AFloatingActor::GameStart()
{
	GameStarted= true;
}


void AFloatingActor::RepeatingFunc() //불이 꺼져있으면 램프에 불 생성
{
	if (!colored && need_change_color) {
		pressed = false;
		need_change_color = false;
		delay_time = delay();
		GetWorldTimerManager().SetTimer(CountdownTimerHandle2, FTimerDelegate::CreateLambda([&]() //delay time만큼의 delay 후 램프에 불 키기
			{
				int length = num_lamp;
				randint = FMath::RandRange(0, num_lamp - 1);
				UStaticMeshComponent* mesh = Lamps[randint]->FindComponentByClass<UStaticMeshComponent>();
				mesh->CreateDynamicMaterialInstance(0);
				mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 0.0f, 0.0f));
				colored = true;
				start_time = GetWorld()->GetTimeSeconds();
			}), delay_time, false);
	}
}



float AFloatingActor::delay() 
{
	float rand_time = FMath::RandRange(0.3f, 2.0f);
	return rand_time;
}

void AFloatingActor::BindToInput()
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
		if (InputComponent)
		{
			InputComponent->BindKey(key_set[0], IE_Pressed, this, &AFloatingActor::is_Pressed1);
			
			if (num_lamp >= 2) InputComponent->BindKey(key_set[1], IE_Pressed, this, &AFloatingActor::is_Pressed2);
			if (num_lamp >= 4)
			{
				InputComponent->BindKey(key_set[2], IE_Pressed, this, &AFloatingActor::is_Pressed3);
				InputComponent->BindKey(key_set[3], IE_Pressed, this, &AFloatingActor::is_Pressed4);
			}
			/*
			if (num_lamp >= 8) {

				InputComponent->BindKey(key_set[4], IE_Pressed, this, &AFloatingActor::is_Pressed5);
				InputComponent->BindKey(key_set[5], IE_Pressed, this, &AFloatingActor::is_Pressed6);
				InputComponent->BindKey(key_set[6], IE_Pressed, this, &AFloatingActor::is_Pressed7);
				InputComponent->BindKey(key_set[7], IE_Pressed, this, &AFloatingActor::is_Pressed8);
			};*/
			// Now hook up our InputComponent to one in a Player
			// Controller, so that input flows down to us
			EnableInput(GetWorld()->GetFirstPlayerController());
		}
}

void AFloatingActor::is_Pressed1()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 0) { 				
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint+1);
		Press.push_back(1);

		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"),react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;

		if (num_lamp == 2) {
			DD::DATA d;
			d.RT = react_time;
			d.COR = isCorrect;
			D.load_data(d);
			UE_LOG(LogTemp, Log, TEXT("1 in lamp2"));
		}
		
		//(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 1, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);
		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 1;
		writeColor = randint + 1;
		
		coloring();

		
	}
}

void AFloatingActor::is_Pressed2()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 1) {
			
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint+1);
		Press.push_back(2);

    	react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		if (num_lamp == 2) {
			DD::DATA d;
			d.RT = react_time;
			d.COR = isCorrect;
			D.load_data(d);
			UE_LOG(LogTemp, Log, TEXT("2 in lamp2") );
			
		}

		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);
		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 2;
		writeColor = randint + 1;

		coloring();



	}
}

void AFloatingActor::is_Pressed3()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 2){
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint + 1);
		Press.push_back(3);


		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;


		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 3, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);
		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 3;
		writeColor = randint + 1;

		coloring();

	}
}

void AFloatingActor::is_Pressed4()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 3) {
			isCorrect = 1;
			correctTotal++;
		}

		Lit.push_back(randint + 1);
		Press.push_back(4);

		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;

		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);


		writeCorrect = isCorrect;
		write_to_file = true;
		num_pressed = 4;
		writeColor = randint + 1;

		coloring();

	}
}

/*
void AFloatingActor::is_Pressed5()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 4) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);


		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}


void AFloatingActor::is_Pressed6()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 5) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);


		//UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}

void AFloatingActor::is_Pressed7()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 6) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);


	//	UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}

void AFloatingActor::is_Pressed8()
{
	if (colored) {
		end_time = GetWorld()->GetTimeSeconds();
		if (randint == 7) isCorrect = 1;
		react_time = end_time - start_time;
		//FName name(*FString::Printf(TEXT("%f"), react_time));
		//player1.isCorrect = isCorrect;
		total_react_time += react_time;
		DD::DATA d;
		d.RT = react_time;
		d.COR = isCorrect;
		D.load_data(d);

//
	//	UE_LOG(LogTemp, Log, TEXT("IsCorrect : %d, Lamp : %d, Pressed : 2, Reaction time : %f seconds"), isCorrect, randint + 1, react_time);

		coloring();

	}
}
*/



void AFloatingActor::is_PressedE(){	
	string a = DRIFT_DIFFUSION_MODEL::runOptimizer();	
	//UE_LOG(LogTemp, Log, TEXT("%s" ),a);

	for (int three = 0; three < num_Big_Trial; three++) {
		HC::DATA d;

		d.N = N[three];
		d.RT =RT[three];
		//UE_LOG(LogTemp, Log, TEXT("%d, %f"), N[three],RT[three]);

				
	
		H.load_data(d);
	}

	string b = HICKS_LAW::runOptimizer();
	H.clear();

	for (int three = 0; three < num_Big_Trial; three++) {
		HC::DATA d;

		d.RT = RT[three];

		int S1 = 0;
		int S2 = 0;
		int S3 = 0;
		int S4 = 0;

		int R1 = 0;
		int R2 = 0;
		int R3 = 0;
		int R4 = 0;
		
		int SR11 = 0;
		int SR12 = 0;
		int SR13 = 0;
		int SR14 = 0;

		int SR21 = 0;
		int SR22 = 0;
		int SR23 = 0;
		int SR24 = 0;

		int SR31 = 0;
		int SR32 = 0;
		int SR33 = 0;
		int SR34 = 0;

		int SR41 = 0;
		int SR42 = 0;
		int SR43 = 0;
		int SR44 = 0;


		for (int hundred = three * num_trial; hundred < three * num_trial + num_trial; hundred++) {

			if (Lit[hundred] == 1) {
				S1++;

				if (Press[hundred] == 1) { R1++;	SR11++; }
				else if (Press[hundred] == 2) { R2++;	SR12++; }
				else if (Press[hundred] == 3) { R3++;	SR13++; }
				else if (Press[hundred] == 4) { R4++;	SR14++; }

			}
			if (Lit[hundred] == 2) {
				S2++;

				if (Press[hundred] == 1) { R1++;	SR21++; }
				else if (Press[hundred] == 2) { R2++;	SR22++; }
				else if (Press[hundred] == 3) { R3++;	SR23++; }
				else if (Press[hundred] == 4) { R4++;	SR24++; }

			}
			if (Lit[hundred] == 3) {
				S3++;

				if (Press[hundred] == 1) { R1++;	SR31++; }
				else if (Press[hundred] == 2) { R2++;	SR32++; }
				else if (Press[hundred] == 3) { R3++;	SR33++; }
				else if (Press[hundred] == 4) { R4++;	SR34++; }

			}
			if (Lit[hundred] == 4) {
				S4++;

				if (Press[hundred] == 1) { R1++;	SR41++; }
				else if (Press[hundred] == 2) { R2++;	SR42++; }
				else if (Press[hundred] == 3) { R3++;	SR43++; }
				else if (Press[hundred] == 4) { R4++;	SR44++; }

			}

		}

		float HS = -log2((1.0f / float(N[three])));
		float HR = 0;
		float HSR = 0;

		if (N[three] == 1) {
			HR = -(float(R1) / 80.0f) * log2(float(R1) / 80.0f);
			HSR = -(float(SR11) / 80.0f) * log2(float(SR11) / 80.0f);
		}
		else if (N[three] == 2) {
			if (R1 != 0) {HR -= (float(R1) / 80.0f) * log2(float(R1) / 80.0f);}
			if (R2 != 0) {HR -= (float(R2) / 80.0f) * log2(float(R2) / 80.0f);}
			if (SR11 != 0) {HSR -= (float(SR11) / 80.0f) * log2(float(SR11) / 80.0f);}
			if (SR12 != 0) {HSR -= (float(SR12) / 80.0f) * log2(float(SR12) / 80.0f);}
			if (SR21 != 0) {HSR -= (float(SR21) / 80.0f) * log2(float(SR21) / 80.0f);}
			if (SR22 != 0) {HSR -= (float(SR22) / 80.0f) * log2(float(SR22) / 80.0f);}
		}
		else if (N[three] == 4) {
			if (R1 != 0) {	HR -= (float(R1) / 80.0f) * log2(float(R1) / 80.0f);}
			if (R2 != 0) {	HR -= (float(R2) / 80.0f) * log2(float(R2) / 80.0f);}
			if (R3 != 0) {	HR -= (float(R3) / 80.0f) * log2(float(R3) / 80.0f);}
			if (R4 != 0) {	HR -= (float(R4) / 80.0f) * log2(float(R4) / 80.0f);}

			if (SR11 != 0) {HSR -= (float(SR11) / 80.0f) * log2(float(SR11) / 80.0f);}
			if (SR12 != 0) {HSR -= (float(SR12) / 80.0f) * log2(float(SR12) / 80.0f);}
			if (SR13 != 0) {HSR -= (float(SR13) / 80.0f) * log2(float(SR13) / 80.0f);}
			if (SR14 != 0) {HSR -= (float(SR14) / 80.0f) * log2(float(SR14) / 80.0f);}
			if (SR21 != 0) {HSR -= (float(SR21) / 80.0f) * log2(float(SR21) / 80.0f);}
			if (SR22 != 0) {HSR -= (float(SR22) / 80.0f) * log2(float(SR22) / 80.0f);}
			if (SR23 != 0) {HSR -= (float(SR23) / 80.0f) * log2(float(SR23) / 80.0f);}
			if (SR24 != 0) {HSR -= (float(SR24) / 80.0f) * log2(float(SR24) / 80.0f);}
			if (SR31 != 0) {HSR -= (float(SR31) / 80.0f) * log2(float(SR31) / 80.0f);}
			if (SR32 != 0) {HSR -= (float(SR32) / 80.0f) * log2(float(SR32) / 80.0f);}
			if (SR33 != 0) {HSR -= (float(SR33) / 80.0f) * log2(float(SR33) / 80.0f);}
			if (SR34 != 0) {HSR -= (float(SR34) / 80.0f) * log2(float(SR34) / 80.0f);}
			if (SR41 != 0) {HSR -= (float(SR41) / 80.0f) * log2(float(SR41) / 80.0f);}
			if (SR42 != 0) {HSR -= (float(SR42) / 80.0f) * log2(float(SR42) / 80.0f);}
			if (SR43 != 0) {HSR -= (float(SR43) / 80.0f) * log2(float(SR43) / 80.0f);}
			if (SR44 != 0) {HSR -= (float(SR44) / 80.0f) * log2(float(SR44) / 80.0f);}
		}

		//UE_LOG(LogTemp, Log, TEXT("%f,%f,%f"), HS, HR, HSR);

		//UE_LOG(LogTemp, Log, TEXT("%d,%d,%d,%d"), R1, R2, R3,R4);
		//UE_LOG(LogTemp, Log, TEXT("%d,%d,%d,%d"), S1, S2, S3, S4);
		//UE_LOG(LogTemp, Log, TEXT("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"), SR11, SR12, SR13, SR14, SR21, SR22, SR23, SR24, SR31, SR32, SR33, SR34, SR41, SR42, SR43, SR44);



		//UE_LOG(LogTemp, Log, TEXT("%d"), N[three]);

		float Nelog2 = HS + HR - HSR;
		//UE_LOG(LogTemp, Log, TEXT("%f"), Nelog2);
		d.N = pow(2,Nelog2);

		//UE_LOG(LogTemp, Log, TEXT("%f,%f"), pow(2, Nelog2) , RT[three]);
		H.load_data(d);
	}
	string c = HICKS_LAW::runOptimizer();

	b = b + ',' + c + string_format(",%f,%f", 1.0f - (float(correctTotal) / 240.0f), (RT[0] + RT[1] + RT[2]) / 3.0f);

	
	ResultData = (a.c_str());
	ResultData2 = (b.c_str());
	UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData);
	UE_LOG(LogTemp, Log, TEXT("%s"), *ResultData2);

	DataSended = true;

	//output_file1.close();
	

}


void AFloatingActor::LocateMaterial(int num_of_cube, TArray<AActor*> Lamp, TArray<AActor*> Button ) {

	for (int i = 0; i < num_of_cube; i++) {
		Lamp[i]->SetActorLocation(FVector(-1250, 600 + interval * i, 500));
		Button[i]->SetActorLocation(FVector(-1250, 600 + interval * i, 100));
	}


	for (int i = 7; i >= num_of_cube; i--) {
		Lamp[i]->SetActorLocation(FVector(-5000, 600 + interval * i, 500));
		Button[i]->SetActorLocation(FVector(-5000, 600 + interval * i, 100));
	}

	BindToInput();
}


void AFloatingActor::coloring()
{
	UStaticMeshComponent* mesh = Lamps[randint]->FindComponentByClass<UStaticMeshComponent>();
	mesh->CreateDynamicMaterialInstance(0);
	mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.0f, 1.0f, 1.0f));
	trial++;
	pressed = true;
	colored = false;
	need_change_color = true;
	isCorrect = 0.0f;
}


void AFloatingActor::Set2DView() {
	SpecificPlayer1->SetViewTarget(camera1);
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
}