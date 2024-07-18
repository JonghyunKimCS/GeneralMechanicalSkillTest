<<<<<<< HEAD
#include "FittsLaw.h"

void FittsLaw::set_param(float _a, float _b)
{
	a = _a; b = _b;
}

void FittsLaw::debug_print_param(bool data_flag)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	if (data_flag)
	{
		if (input_data.empty()) { cout << "No input data given!" << endl; }
		else
		{
			for (const auto& d : input_data)
			{
				cout << "Data -------------" << endl;
				cout << "ID = \t" << d.ID << endl;
				cout << "MT = \t" << d.MT << endl;
			}
		}
	}
}


void FittsLaw::clear() {
	input_data.clear();
}


void FittsLaw::load_data(FT::DATA d)
{
	/*
	input_data.clear();
	data_fn = filename;

	fstream file;
	file.open(filename, ios::in);
	string data;

	while (getline(file, data, '\n'))
	{
		stringstream ss(data);
		string temp;
		FT::DATA d;
		int idx = 0;
		float id_W, id_D;

		while (getline(ss, temp, ','))
		{
			if (idx == 0) { id_W = stof(temp); idx++; }
			else if (idx == 1)
			{
				id_D = stof(temp); idx++;
				d.ID = log2(id_D / id_W + 1);
			}
			else // idx == 2
			{
				d.MT = stof(temp) / 1000;
			}
		}
		
	}

	file.close();*/
	input_data.push_back(d);
}

float FittsLaw::predict(FT::DATA d)
{
	return a + b * d.ID;
}

float FittsLaw::COD()
{
	float mt_bar = 0.0;
	for (const auto& d : input_data) mt_bar += d.MT;
	mt_bar /= input_data.size();
	float SSE = 0.0f;
	float SST = 0.0f;
	for (const auto& d : input_data)
	{
		SST += pow(d.MT - mt_bar, 2.0f);
		SSE += pow(d.MT - predict(d), 2.0f);
	}
	return 1.0f - SSE / SST;
}

void FittsLaw::linear_regression()
{
	float mt_bar = 0.0f;
	float id_bar = 0.0f;
	for (const auto& d : input_data) { mt_bar += d.MT; id_bar += d.ID; }
	mt_bar /= input_data.size();
	id_bar /= input_data.size();

	b = 0.0f;
	float dem = 0.0f;
	for (const auto& d : input_data)
	{
		b += (d.MT - mt_bar) * (d.ID - id_bar);
		dem += pow(d.ID - id_bar, 2.0f);
	}
	b /= dem;

	a = mt_bar - b * id_bar;
}

string FittsLaw::result_header()
{
	return "Path,a,b,R^2\n";
}

string FittsLaw::result_csv_form()
{
	return data_fn + string_format("%f,%f,%f\n", a, b, COD());
=======
#include "FittsLaw.h"

void FittsLaw::set_param(float _a, float _b)
{
	a = _a; b = _b;
}

void FittsLaw::debug_print_param(bool data_flag)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	if (data_flag)
	{
		if (input_data.empty()) { cout << "No input data given!" << endl; }
		else
		{
			for (const auto& d : input_data)
			{
				cout << "Data -------------" << endl;
				cout << "ID = \t" << d.ID << endl;
				cout << "MT = \t" << d.MT << endl;
			}
		}
	}
}


void FittsLaw::clear() {
	input_data.clear();
}


void FittsLaw::load_data(FT::DATA d)
{
	/*
	input_data.clear();
	data_fn = filename;

	fstream file;
	file.open(filename, ios::in);
	string data;

	while (getline(file, data, '\n'))
	{
		stringstream ss(data);
		string temp;
		FT::DATA d;
		int idx = 0;
		float id_W, id_D;

		while (getline(ss, temp, ','))
		{
			if (idx == 0) { id_W = stof(temp); idx++; }
			else if (idx == 1)
			{
				id_D = stof(temp); idx++;
				d.ID = log2(id_D / id_W + 1);
			}
			else // idx == 2
			{
				d.MT = stof(temp) / 1000;
			}
		}
		
	}

	file.close();*/
	input_data.push_back(d);
}

float FittsLaw::predict(FT::DATA d)
{
	return a + b * d.ID;
}

float FittsLaw::COD()
{
	float mt_bar = 0.0;
	for (const auto& d : input_data) mt_bar += d.MT;
	mt_bar /= input_data.size();
	float SSE = 0.0f;
	float SST = 0.0f;
	for (const auto& d : input_data)
	{
		SST += pow(d.MT - mt_bar, 2.0f);
		SSE += pow(d.MT - predict(d), 2.0f);
	}
	return 1.0f - SSE / SST;
}

void FittsLaw::linear_regression()
{
	float mt_bar = 0.0f;
	float id_bar = 0.0f;
	for (const auto& d : input_data) { mt_bar += d.MT; id_bar += d.ID; }
	mt_bar /= input_data.size();
	id_bar /= input_data.size();

	b = 0.0f;
	float dem = 0.0f;
	for (const auto& d : input_data)
	{
		b += (d.MT - mt_bar) * (d.ID - id_bar);
		dem += pow(d.ID - id_bar, 2.0f);
	}
	b /= dem;

	a = mt_bar - b * id_bar;
}

string FittsLaw::result_header()
{
	return "Path,a,b,R^2\n";
}

string FittsLaw::result_csv_form()
{
	return data_fn + string_format("%f,%f,%f\n", a, b, COD());
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
}