<<<<<<< HEAD
#include "MovingTargetSelection.h"

void MovingTargetSelection::set_param(float _c1, float _c2, float _c3, float _c4)
{
	c1 = _c1; c2 = _c2; c3 = _c3; c4 = _c4; 
}

void MovingTargetSelection::debug_print_param(bool data_flag)
{
	cout << "Parameters:" << endl;
	cout << "c1 = " << c1 << endl;
	cout << "c2 = " << c2 << endl;
	cout << "c3 = " << c3 << endl;
	cout << "c4 = " << c4 << endl;
	

	if (data_flag)
	{
		if (input_data.empty()) { cout << "No input data given!" << endl; }
		else
		{
			for (const auto& d : input_data)
			{
				cout << "Data -------------" << endl;
				cout << "p = \t" << d.p << endl;
				cout << "t_zone = \t" << d.t_zone << endl;
				cout << "t_cue = \t" << d.t_cue << endl;				
				cout << "r_err = \t" << d.y << endl;
			}
		}
	}
}

void MovingTargetSelection::clear() {
	input_data.clear();
}


void MovingTargetSelection::load_data(MTS::DATA d)
{
	//input_data.clear();
	/*data_fn = filename;

	fstream file;
	file.open(filename, ios::in);
	string data;

	while (getline(file, data, '\n'))
	{
		stringstream ss(data);
		string temp;
		MTS::DATA d;
		int idx = 0;
		int n_ans = 0;
		int n_cor = 0;

		while (getline(ss, temp, ','))
		{
			if (idx == 0) { d.p = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 1) { d.t_zone = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 2) { d.t_cue = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 3) { d.s = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 4) { d.r = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 5) { d.l = stof(temp.substr(1)) / 1000; idx++; }
			else
			{
				n_ans++;
				if (stoi(temp) == 1) n_cor++;
			}
		}
		d.y = 1 - (float)n_cor / (float)n_ans;
		input_data.push_back(d);
	}

	file.close();*/
	input_data.push_back(d);
}

float MovingTargetSelection::predict(MTS::DATA d)
{
	float _p = d.p;
	float _t_zone = d.t_zone;
	float _t_cue = max(d.t_cue , SMALL_FLOAT);

	float w_integ = c1 * _t_zone ;
	float s_t = c2 * _p;
	float s_v = c3 + 1 / (exp(c4 * _t_cue) - 1);
	float s_integ = sqrt(pow(s_t, 2.0f) * pow(s_v, 2.0f) / (pow(s_t, 2.0f) + pow(s_v, 2.0f)));


	return 1.0f - 0.5f * (erf((_t_zone - w_integ) / (s_integ * sqrt(2.0f))) +
							erf(w_integ / (s_integ * sqrt(2.0f))));
}

float MovingTargetSelection::LSQ()
{
	float err = 0.0;
	for (const auto& d : input_data)
	{
		err += pow(predict(d) - d.y, 2.0f);
	}
	return err;
}

float MovingTargetSelection::COD()
{
	float y_m = 0.0;
	for (const auto& d : input_data) y_m += d.y;
	y_m /= input_data.size();

	float SSE = 0.0f;
	float SST = 0.0f;

	for (const auto& d : input_data)
	{
		SSE += pow(d.y - predict(d), 2.0f);
		SST += pow(d.y - y_m, 2.0f);
	}

	return 1.0f - SSE / SST;
}

string MovingTargetSelection::result_header()
{
	return "Path,c1,c2,c3,c4,R^2\n";
}

string MovingTargetSelection::result_csv_form()
{
	return data_fn + string_format("%f,%f,%f,%f,%f",
									c1, c2, c3, c4, COD());
=======
#include "MovingTargetSelection.h"

void MovingTargetSelection::set_param(float _c1, float _c2, float _c3, float _c4)
{
	c1 = _c1; c2 = _c2; c3 = _c3; c4 = _c4; 
}

void MovingTargetSelection::debug_print_param(bool data_flag)
{
	cout << "Parameters:" << endl;
	cout << "c1 = " << c1 << endl;
	cout << "c2 = " << c2 << endl;
	cout << "c3 = " << c3 << endl;
	cout << "c4 = " << c4 << endl;
	

	if (data_flag)
	{
		if (input_data.empty()) { cout << "No input data given!" << endl; }
		else
		{
			for (const auto& d : input_data)
			{
				cout << "Data -------------" << endl;
				cout << "p = \t" << d.p << endl;
				cout << "t_zone = \t" << d.t_zone << endl;
				cout << "t_cue = \t" << d.t_cue << endl;				
				cout << "r_err = \t" << d.y << endl;
			}
		}
	}
}

void MovingTargetSelection::clear() {
	input_data.clear();
}


void MovingTargetSelection::load_data(MTS::DATA d)
{
	//input_data.clear();
	/*data_fn = filename;

	fstream file;
	file.open(filename, ios::in);
	string data;

	while (getline(file, data, '\n'))
	{
		stringstream ss(data);
		string temp;
		MTS::DATA d;
		int idx = 0;
		int n_ans = 0;
		int n_cor = 0;

		while (getline(ss, temp, ','))
		{
			if (idx == 0) { d.p = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 1) { d.t_zone = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 2) { d.t_cue = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 3) { d.s = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 4) { d.r = stof(temp.substr(1)) / 1000; idx++; }
			else if (idx == 5) { d.l = stof(temp.substr(1)) / 1000; idx++; }
			else
			{
				n_ans++;
				if (stoi(temp) == 1) n_cor++;
			}
		}
		d.y = 1 - (float)n_cor / (float)n_ans;
		input_data.push_back(d);
	}

	file.close();*/
	input_data.push_back(d);
}

float MovingTargetSelection::predict(MTS::DATA d)
{
	float _p = d.p;
	float _t_zone = d.t_zone;
	float _t_cue = max(d.t_cue , SMALL_FLOAT);

	float w_integ = c1 * _t_zone ;
	float s_t = c2 * _p;
	float s_v = c3 + 1 / (exp(c4 * _t_cue) - 1);
	float s_integ = sqrt(pow(s_t, 2.0f) * pow(s_v, 2.0f) / (pow(s_t, 2.0f) + pow(s_v, 2.0f)));


	return 1.0f - 0.5f * (erf((_t_zone - w_integ) / (s_integ * sqrt(2.0f))) +
							erf(w_integ / (s_integ * sqrt(2.0f))));
}

float MovingTargetSelection::LSQ()
{
	float err = 0.0;
	for (const auto& d : input_data)
	{
		err += pow(predict(d) - d.y, 2.0f);
	}
	return err;
}

float MovingTargetSelection::COD()
{
	float y_m = 0.0;
	for (const auto& d : input_data) y_m += d.y;
	y_m /= input_data.size();

	float SSE = 0.0f;
	float SST = 0.0f;

	for (const auto& d : input_data)
	{
		SSE += pow(d.y - predict(d), 2.0f);
		SST += pow(d.y - y_m, 2.0f);
	}

	return 1.0f - SSE / SST;
}

string MovingTargetSelection::result_header()
{
	return "Path,c1,c2,c3,c4,R^2\n";
}

string MovingTargetSelection::result_csv_form()
{
	return data_fn + string_format("%f,%f,%f,%f,%f",
									c1, c2, c3, c4, COD());
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
}