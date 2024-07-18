<<<<<<< HEAD
#include "HicksLaw.h"

void HicksLaw::set_param(float _a, float _b)
{
	a = _a; b = _b;
}

void HicksLaw::debug_print_param(bool data_flag)
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
				cout << "N = \t" << d.N << endl;
				cout << "RT = \t" << d.RT << endl;
			}
		}
	}
}

void HicksLaw::clear() {
	input_data.clear();
}

void HicksLaw::load_data(HC::DATA d)
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
		HC::DATA d;
		int idx = 0;

		while (getline(ss, temp, ','))
		{
			if (idx == 0) { d.N = stof(temp); idx++; }
			else { d.RT = stof(temp); }
		}
		input_data.push_back(d);
	}

	file.close();*/
	input_data.push_back(d);
}

float HicksLaw::predict(HC::DATA d)
{
	return a + b * log2(d.N);
}

float HicksLaw::COD()
{
	float mt_bar = 0.0;
	for (const auto& d : input_data) mt_bar += d.RT;
	mt_bar /= input_data.size();
	float SSE = 0.0f;
	float SST = 0.0f;
	for (const auto& d : input_data)
	{
		SST += pow(d.RT - mt_bar, 2.0f);
		SSE += pow(d.RT - predict(d), 2.0f);
	}
	return 1.0f - SSE / SST;
}

void HicksLaw::linear_regression()
{
	float mt_bar = 0.0f;
	float id_bar = 0.0f;
	for (const auto& d : input_data) { mt_bar += d.RT; id_bar += log2(d.N); }
	mt_bar /= input_data.size();
	id_bar /= input_data.size();

	b = 0.0f;
	float dem = 0.0f;
	for (const auto& d : input_data)
	{
		b += (d.RT - mt_bar) * (log2(d.N) - id_bar);
		dem += pow(log2(d.N) - id_bar, 2.0f);
	}
	b /= dem;

	a = mt_bar - b * id_bar;
}

string HicksLaw::result_header()
{
	return "Path,a,b,R^2\n";
}

string HicksLaw::result_csv_form()
{
	return data_fn + string_format("%f,%f,%f\n", a, b, COD());
=======
#include "HicksLaw.h"

void HicksLaw::set_param(float _a, float _b)
{
	a = _a; b = _b;
}

void HicksLaw::debug_print_param(bool data_flag)
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
				cout << "N = \t" << d.N << endl;
				cout << "RT = \t" << d.RT << endl;
			}
		}
	}
}

void HicksLaw::clear() {
	input_data.clear();
}

void HicksLaw::load_data(HC::DATA d)
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
		HC::DATA d;
		int idx = 0;

		while (getline(ss, temp, ','))
		{
			if (idx == 0) { d.N = stof(temp); idx++; }
			else { d.RT = stof(temp); }
		}
		input_data.push_back(d);
	}

	file.close();*/
	input_data.push_back(d);
}

float HicksLaw::predict(HC::DATA d)
{
	return a + b * log2(d.N);
}

float HicksLaw::COD()
{
	float mt_bar = 0.0;
	for (const auto& d : input_data) mt_bar += d.RT;
	mt_bar /= input_data.size();
	float SSE = 0.0f;
	float SST = 0.0f;
	for (const auto& d : input_data)
	{
		SST += pow(d.RT - mt_bar, 2.0f);
		SSE += pow(d.RT - predict(d), 2.0f);
	}
	return 1.0f - SSE / SST;
}

void HicksLaw::linear_regression()
{
	float mt_bar = 0.0f;
	float id_bar = 0.0f;
	for (const auto& d : input_data) { mt_bar += d.RT; id_bar += log2(d.N); }
	mt_bar /= input_data.size();
	id_bar /= input_data.size();

	b = 0.0f;
	float dem = 0.0f;
	for (const auto& d : input_data)
	{
		b += (d.RT - mt_bar) * (log2(d.N) - id_bar);
		dem += pow(log2(d.N) - id_bar, 2.0f);
	}
	b /= dem;

	a = mt_bar - b * id_bar;
}

string HicksLaw::result_header()
{
	return "Path,a,b,R^2\n";
}

string HicksLaw::result_csv_form()
{
	return data_fn + string_format("%f,%f,%f\n", a, b, COD());
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
}