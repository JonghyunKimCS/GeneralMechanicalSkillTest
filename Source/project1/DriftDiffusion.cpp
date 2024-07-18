<<<<<<< HEAD
#include "DriftDiffusion.h"

void DriftDiffusion::set_param(float _a, float _nu, float _eta, float _sz, float _st,float _T_err)
{
	a = _a; nu = _nu; eta = _eta; sz = _sz; st = _st; z = _a / 2; T_err = _T_err;
}

void DriftDiffusion::debug_print_param(bool data_flag)
{
	cout << "Parameters:" << endl;
	cout << "a = \t" << a << endl;
	cout << "nu = \t" << nu << endl;
	cout << "eta = \t" << eta << endl;
	cout << "sz = \t" << sz << endl;
	cout << "st = \t" << st << endl;
	cout << "z = \t" << z << endl;

	if (data_flag)
	{
		if (input_data.empty()) { cout << "No input data given!" << endl; }
		else
		{
			cout << "Data -------------" << endl;
			for (const auto& data : input_data)
			{
				cout << "RT = " << data.RT << " (" << data.COR << ")" << endl;
			}
		}

	}

}
void DriftDiffusion::clear()
{
	input_data.clear();
}
void DriftDiffusion::load_data(DD::DATA d)
{

	
	/*
	* input_data.clear();
	data_fn = filename;

	fstream file;
	file.open(filename, ios::in);
	string data;
	while (!file.eof())
	{
		DD::DATA d;
		getline(file, data, '\n');
		stringstream ss(data);
		string temp;
		bool time = true;

		while (getline(ss, temp, ','))
		{
			if (time) { d.RT = stof(temp); time = false; }
			else { d.COR = stoi(temp); input_data.push_back(d); }
		}
	}
	file.close();
	*/

	input_data.push_back(d);

}

float DriftDiffusion::likelihood()
{
	rt_cor.clear();
	rt_err.clear();

	// Set random distributions
	float smp_nu, smp_T_err, smp_z, evidence;
	normal_distribution<float> dist_g(nu, eta);
	uniform_real_distribution<float> dist_u(0.0f, 1.0f);
	random_device rd;
	mt19937 gen(rd());

	
	// ------------ Part 1. Simulation of reaction time
	//for (int i = 0; i < MINIMAL_NUM_OF_INTER_TRIAL; i++)
	int trial = 0;
	while (true)
	{
		while (true)
		{
			smp_nu = dist_g(gen);
			smp_T_err = T_err + (dist_u(gen) - 0.5f) * st;
			smp_z = (dist_u(gen) - 0.5f) * sz;
			evidence = z + smp_z;

			if (smp_nu > 0.0f &&
				smp_T_err > 0.0f &&
				evidence > 0.0f &&
				evidence < a) break;


		}

		float p = (1.0f + smp_nu * sqrt(step_size) / s) * 0.5f;
		float delta = s * sqrt(step_size);
		int num_step = 0;

		binomial_distribution<int> dist_b(1, p);

		while (true)
		{
			int sampling = dist_b(gen);
			if (sampling) evidence += delta;
			else evidence -= delta;

			num_step++;

			if (evidence >= a)
			{
				rt_cor.push_back(num_step * step_size + smp_T_err);
				break;
			}
			if (evidence <= 0.0f)
			{
				rt_err.push_back(num_step * step_size + smp_T_err);
				break;
			}
		}
		trial++;

		// 
		if (trial >= MINIMAL_NUM_OF_INTER_TRIAL && rt_err.size() > 0) break;
	}
	// ------------ Part 1 End.
	
	// ------------ Part 2. Build Cumulative Dist. Function
	size_t num_cor = rt_cor.size();
	size_t num_err = rt_err.size();

	vector<float> cdf_cor;
	vector<float> cdf_err;

	float unit_cor = 1.0f / num_cor;
	float unit_err = 1.0f / num_err;

	float prob_of_cor = (float)num_cor / ((float)num_cor + (float)num_err);
	float prob_of_err = 1.0f - prob_of_cor;

	sort(rt_cor.begin(), rt_cor.end());
	sort(rt_err.begin(), rt_err.end());

	// Build CDF for correct case
	float min_rt_cor = rt_cor.at(0);
	float max_rt_cor = rt_cor.back();

	int padding_size_l = (int)(1000 * min_rt_cor) + 999;
	int padding_size_r = 99999 - (int)(1000 * max_rt_cor);
	
	// Left Padding
	vector<float> padding_l;
	for (int i = 0; i < padding_size_l; i++) padding_l.push_back(-1 + 0.001f * i);
	rt_cor.insert(rt_cor.begin(), padding_l.begin(), padding_l.end());
	padding_l.clear();
	// Right Padding
	for (int i = 1; i <= padding_size_r; i++) rt_cor.push_back(max_rt_cor + 0.001f * i);

	// Create CDF
	for (int i = 0; i < padding_size_l; i++) cdf_cor.push_back(0);
	for (int i = 1; i <= num_cor; i++) cdf_cor.push_back(i * unit_cor * prob_of_cor);
	for (int i = 0; i < padding_size_r; i++) cdf_cor.push_back(prob_of_cor);
	
	// Check duplicate!
	size_t e = padding_size_l;
	while (true)
	{
		if (rt_cor.at(e) == rt_cor.at(e + 1))
		{
			cdf_cor.at(e) = cdf_cor.at(e + 1);
			cdf_cor.erase(cdf_cor.begin() + e + 1);
			rt_cor.erase(rt_cor.begin() + e + 1);
		}
		else
		{
			e++;
			if (e == num_cor + padding_size_l) break;
		}
	}

	// Build CDF for error case
	float min_rt_err = rt_err.at(0);
	float max_rt_err = rt_err.back();

	padding_size_l = (int)(1000 * min_rt_err) + 999;
	padding_size_r = 99999 - (int)(1000 * max_rt_err);

	// Left Padding
	for (int i = 0; i < padding_size_l; i++) padding_l.push_back(-1 + 0.001f * i);
	rt_err.insert(rt_err.begin(), padding_l.begin(), padding_l.end());
	padding_l.clear();
	// Right Padding
	for (int i = 1; i <= padding_size_r; i++) rt_err.push_back(max_rt_err + 0.001f * i);

	// Create CDF
	for (int i = 0; i < padding_size_l; i++) cdf_err.push_back(0);
	for (int i = 1; i <= num_err; i++) cdf_err.push_back(i * unit_err * prob_of_err);
	for (int i = 0; i < padding_size_r; i++) cdf_err.push_back(prob_of_err);
	
	// Check duplicate!
	e = padding_size_l;
	while (true)
	{
		if (rt_err.at(e) == rt_err.at(e + 1))
		{
			cdf_err.at(e) = cdf_err.at(e + 1);
			cdf_err.erase(cdf_err.begin() + e + 1);
			rt_err.erase(rt_err.begin() + e + 1);
		}
		else
		{
			e++;
			if (e == num_err + padding_size_l) break;
		}
	}
	// ------------ Part 2 End.
	
	// ------------ Part 3. Calculate Likelihood
	float ll = 0;
	for (const auto& data : input_data)
	{
		float rt = data.RT;
		int cor = data.COR;
		float cdf_t1 = 0;
		float cdf_t2 = 0;

		if (cor)
		{
			// Use Binary Search to find closest RT set
			size_t il = 0; size_t ir = rt_cor.size() - 1;
			size_t im = (il + ir) / 2;
			for (int i = 0; i < (int)log2(ir); i++) // log_2(10000) ~ 14
			{
				if (rt < rt_cor.at(im)) ir = im;
				if (rt > rt_cor.at(im)) il = im;
				im = (il + ir) / 2;
			}
			while (true)
			{
				if (rt >= rt_cor.at(im) && rt <= rt_cor.at(im + 1)) break;
				if (rt < rt_cor.at(im)) im--;
				if (rt > rt_cor.at(im + 1)) im++;
			}

			cdf_t1 = ((cdf_cor.at(im + 1) - cdf_cor.at(im)) * rt +
				rt_cor.at(im + 1) * cdf_cor.at(im) -
				rt_cor.at(im) * cdf_cor.at(im + 1)) / (rt_cor.at(im + 1) - rt_cor.at(im));

			while (true)
			{
				if (rt + dt >= rt_cor.at(im) && rt + dt <= rt_cor.at(im + 1)) break;
				if (rt + dt > rt_cor.at(im + 1)) im++;
			}

			cdf_t2 = ((cdf_cor.at(im + 1) - cdf_cor.at(im)) * (rt + dt) +
				rt_cor.at(im + 1) * cdf_cor.at(im) -
				rt_cor.at(im) * cdf_cor.at(im + 1)) / (rt_cor.at(im + 1) - rt_cor.at(im));
		}
		else
		{
			size_t il = 0; size_t ir = rt_err.size() - 1;
			size_t im = (il + ir) / 2;
			for (int i = 0; i < (int)log2(ir); i++) // log_2(10000) ~ 14
			{
				if (rt < rt_err.at(im)) ir = im;
				if (rt > rt_err.at(im)) il = im;
				im = (il + ir) / 2;
			}
			while (true)
			{
				if (rt >= rt_err.at(im) && rt <= rt_err.at(im + 1)) break;
				if (rt < rt_err.at(im)) im--;
				if (rt > rt_err.at(im + 1)) im++;
			}

			cdf_t1 = ((cdf_err.at(im + 1) - cdf_err.at(im)) * rt +
				rt_err.at(im + 1) * cdf_err.at(im) -
				rt_err.at(im) * cdf_err.at(im + 1)) / (rt_err.at(im + 1) - rt_err.at(im));
			
			while (true)
			{
				if (rt + dt >= rt_err.at(im) && rt + dt <= rt_err.at(im + 1)) break;
				if (rt + dt > rt_err.at(im + 1)) im++;
			}

			cdf_t2 = ((cdf_err.at(im + 1) - cdf_err.at(im)) * (rt + dt) +
				rt_err.at(im + 1) * cdf_err.at(im) -
				rt_err.at(im) * cdf_err.at(im + 1)) / (rt_err.at(im + 1) - rt_err.at(im));
		}

		float empirical_rt_ll = (cdf_t2 - cdf_t1) / dt;

		if (empirical_rt_ll <= 0) empirical_rt_ll = SMALL_FLOAT;
		ll += log(empirical_rt_ll);
	}

	rt_cor.clear();
	rt_err.clear();
	
	return -ll;
}

float DriftDiffusion::likelihood_avg(int N)
{
	float sum = 0.0f;
	for (int i = 0; i < N; i++)
	{
		sum += likelihood();
	}

	return sum / N;
}

string DriftDiffusion::result_header()
{
	return "Path,a,z,nu,eta,s,sz,st,T_err,likelihood\n";
}

string DriftDiffusion::result_csv_form()
{
	// a, z, nu, eta, s, sz, st, T_er
	return  string_format("%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
					a, z, nu, eta, s, sz, st, T_err, likelihood_avg(100));
}

=======
#include "DriftDiffusion.h"

void DriftDiffusion::set_param(float _a, float _nu, float _eta, float _sz, float _st,float _T_err)
{
	a = _a; nu = _nu; eta = _eta; sz = _sz; st = _st; z = _a / 2; T_err = _T_err;
}

void DriftDiffusion::debug_print_param(bool data_flag)
{
	cout << "Parameters:" << endl;
	cout << "a = \t" << a << endl;
	cout << "nu = \t" << nu << endl;
	cout << "eta = \t" << eta << endl;
	cout << "sz = \t" << sz << endl;
	cout << "st = \t" << st << endl;
	cout << "z = \t" << z << endl;

	if (data_flag)
	{
		if (input_data.empty()) { cout << "No input data given!" << endl; }
		else
		{
			cout << "Data -------------" << endl;
			for (const auto& data : input_data)
			{
				cout << "RT = " << data.RT << " (" << data.COR << ")" << endl;
			}
		}

	}

}
void DriftDiffusion::clear()
{
	input_data.clear();
}
void DriftDiffusion::load_data(DD::DATA d)
{

	
	/*
	* input_data.clear();
	data_fn = filename;

	fstream file;
	file.open(filename, ios::in);
	string data;
	while (!file.eof())
	{
		DD::DATA d;
		getline(file, data, '\n');
		stringstream ss(data);
		string temp;
		bool time = true;

		while (getline(ss, temp, ','))
		{
			if (time) { d.RT = stof(temp); time = false; }
			else { d.COR = stoi(temp); input_data.push_back(d); }
		}
	}
	file.close();
	*/

	input_data.push_back(d);

}

float DriftDiffusion::likelihood()
{
	rt_cor.clear();
	rt_err.clear();

	// Set random distributions
	float smp_nu, smp_T_err, smp_z, evidence;
	normal_distribution<float> dist_g(nu, eta);
	uniform_real_distribution<float> dist_u(0.0f, 1.0f);
	random_device rd;
	mt19937 gen(rd());

	
	// ------------ Part 1. Simulation of reaction time
	//for (int i = 0; i < MINIMAL_NUM_OF_INTER_TRIAL; i++)
	int trial = 0;
	while (true)
	{
		while (true)
		{
			smp_nu = dist_g(gen);
			smp_T_err = T_err + (dist_u(gen) - 0.5f) * st;
			smp_z = (dist_u(gen) - 0.5f) * sz;
			evidence = z + smp_z;

			if (smp_nu > 0.0f &&
				smp_T_err > 0.0f &&
				evidence > 0.0f &&
				evidence < a) break;


		}

		float p = (1.0f + smp_nu * sqrt(step_size) / s) * 0.5f;
		float delta = s * sqrt(step_size);
		int num_step = 0;

		binomial_distribution<int> dist_b(1, p);

		while (true)
		{
			int sampling = dist_b(gen);
			if (sampling) evidence += delta;
			else evidence -= delta;

			num_step++;

			if (evidence >= a)
			{
				rt_cor.push_back(num_step * step_size + smp_T_err);
				break;
			}
			if (evidence <= 0.0f)
			{
				rt_err.push_back(num_step * step_size + smp_T_err);
				break;
			}
		}
		trial++;

		// 
		if (trial >= MINIMAL_NUM_OF_INTER_TRIAL && rt_err.size() > 0) break;
	}
	// ------------ Part 1 End.
	
	// ------------ Part 2. Build Cumulative Dist. Function
	size_t num_cor = rt_cor.size();
	size_t num_err = rt_err.size();

	vector<float> cdf_cor;
	vector<float> cdf_err;

	float unit_cor = 1.0f / num_cor;
	float unit_err = 1.0f / num_err;

	float prob_of_cor = (float)num_cor / ((float)num_cor + (float)num_err);
	float prob_of_err = 1.0f - prob_of_cor;

	sort(rt_cor.begin(), rt_cor.end());
	sort(rt_err.begin(), rt_err.end());

	// Build CDF for correct case
	float min_rt_cor = rt_cor.at(0);
	float max_rt_cor = rt_cor.back();

	int padding_size_l = (int)(1000 * min_rt_cor) + 999;
	int padding_size_r = 99999 - (int)(1000 * max_rt_cor);
	
	// Left Padding
	vector<float> padding_l;
	for (int i = 0; i < padding_size_l; i++) padding_l.push_back(-1 + 0.001f * i);
	rt_cor.insert(rt_cor.begin(), padding_l.begin(), padding_l.end());
	padding_l.clear();
	// Right Padding
	for (int i = 1; i <= padding_size_r; i++) rt_cor.push_back(max_rt_cor + 0.001f * i);

	// Create CDF
	for (int i = 0; i < padding_size_l; i++) cdf_cor.push_back(0);
	for (int i = 1; i <= num_cor; i++) cdf_cor.push_back(i * unit_cor * prob_of_cor);
	for (int i = 0; i < padding_size_r; i++) cdf_cor.push_back(prob_of_cor);
	
	// Check duplicate!
	size_t e = padding_size_l;
	while (true)
	{
		if (rt_cor.at(e) == rt_cor.at(e + 1))
		{
			cdf_cor.at(e) = cdf_cor.at(e + 1);
			cdf_cor.erase(cdf_cor.begin() + e + 1);
			rt_cor.erase(rt_cor.begin() + e + 1);
		}
		else
		{
			e++;
			if (e == num_cor + padding_size_l) break;
		}
	}

	// Build CDF for error case
	float min_rt_err = rt_err.at(0);
	float max_rt_err = rt_err.back();

	padding_size_l = (int)(1000 * min_rt_err) + 999;
	padding_size_r = 99999 - (int)(1000 * max_rt_err);

	// Left Padding
	for (int i = 0; i < padding_size_l; i++) padding_l.push_back(-1 + 0.001f * i);
	rt_err.insert(rt_err.begin(), padding_l.begin(), padding_l.end());
	padding_l.clear();
	// Right Padding
	for (int i = 1; i <= padding_size_r; i++) rt_err.push_back(max_rt_err + 0.001f * i);

	// Create CDF
	for (int i = 0; i < padding_size_l; i++) cdf_err.push_back(0);
	for (int i = 1; i <= num_err; i++) cdf_err.push_back(i * unit_err * prob_of_err);
	for (int i = 0; i < padding_size_r; i++) cdf_err.push_back(prob_of_err);
	
	// Check duplicate!
	e = padding_size_l;
	while (true)
	{
		if (rt_err.at(e) == rt_err.at(e + 1))
		{
			cdf_err.at(e) = cdf_err.at(e + 1);
			cdf_err.erase(cdf_err.begin() + e + 1);
			rt_err.erase(rt_err.begin() + e + 1);
		}
		else
		{
			e++;
			if (e == num_err + padding_size_l) break;
		}
	}
	// ------------ Part 2 End.
	
	// ------------ Part 3. Calculate Likelihood
	float ll = 0;
	for (const auto& data : input_data)
	{
		float rt = data.RT;
		int cor = data.COR;
		float cdf_t1 = 0;
		float cdf_t2 = 0;

		if (cor)
		{
			// Use Binary Search to find closest RT set
			size_t il = 0; size_t ir = rt_cor.size() - 1;
			size_t im = (il + ir) / 2;
			for (int i = 0; i < (int)log2(ir); i++) // log_2(10000) ~ 14
			{
				if (rt < rt_cor.at(im)) ir = im;
				if (rt > rt_cor.at(im)) il = im;
				im = (il + ir) / 2;
			}
			while (true)
			{
				if (rt >= rt_cor.at(im) && rt <= rt_cor.at(im + 1)) break;
				if (rt < rt_cor.at(im)) im--;
				if (rt > rt_cor.at(im + 1)) im++;
			}

			cdf_t1 = ((cdf_cor.at(im + 1) - cdf_cor.at(im)) * rt +
				rt_cor.at(im + 1) * cdf_cor.at(im) -
				rt_cor.at(im) * cdf_cor.at(im + 1)) / (rt_cor.at(im + 1) - rt_cor.at(im));

			while (true)
			{
				if (rt + dt >= rt_cor.at(im) && rt + dt <= rt_cor.at(im + 1)) break;
				if (rt + dt > rt_cor.at(im + 1)) im++;
			}

			cdf_t2 = ((cdf_cor.at(im + 1) - cdf_cor.at(im)) * (rt + dt) +
				rt_cor.at(im + 1) * cdf_cor.at(im) -
				rt_cor.at(im) * cdf_cor.at(im + 1)) / (rt_cor.at(im + 1) - rt_cor.at(im));
		}
		else
		{
			size_t il = 0; size_t ir = rt_err.size() - 1;
			size_t im = (il + ir) / 2;
			for (int i = 0; i < (int)log2(ir); i++) // log_2(10000) ~ 14
			{
				if (rt < rt_err.at(im)) ir = im;
				if (rt > rt_err.at(im)) il = im;
				im = (il + ir) / 2;
			}
			while (true)
			{
				if (rt >= rt_err.at(im) && rt <= rt_err.at(im + 1)) break;
				if (rt < rt_err.at(im)) im--;
				if (rt > rt_err.at(im + 1)) im++;
			}

			cdf_t1 = ((cdf_err.at(im + 1) - cdf_err.at(im)) * rt +
				rt_err.at(im + 1) * cdf_err.at(im) -
				rt_err.at(im) * cdf_err.at(im + 1)) / (rt_err.at(im + 1) - rt_err.at(im));
			
			while (true)
			{
				if (rt + dt >= rt_err.at(im) && rt + dt <= rt_err.at(im + 1)) break;
				if (rt + dt > rt_err.at(im + 1)) im++;
			}

			cdf_t2 = ((cdf_err.at(im + 1) - cdf_err.at(im)) * (rt + dt) +
				rt_err.at(im + 1) * cdf_err.at(im) -
				rt_err.at(im) * cdf_err.at(im + 1)) / (rt_err.at(im + 1) - rt_err.at(im));
		}

		float empirical_rt_ll = (cdf_t2 - cdf_t1) / dt;

		if (empirical_rt_ll <= 0) empirical_rt_ll = SMALL_FLOAT;
		ll += log(empirical_rt_ll);
	}

	rt_cor.clear();
	rt_err.clear();
	
	return -ll;
}

float DriftDiffusion::likelihood_avg(int N)
{
	float sum = 0.0f;
	for (int i = 0; i < N; i++)
	{
		sum += likelihood();
	}

	return sum / N;
}

string DriftDiffusion::result_header()
{
	return "Path,a,z,nu,eta,s,sz,st,T_err,likelihood\n";
}

string DriftDiffusion::result_csv_form()
{
	// a, z, nu, eta, s, sz, st, T_er
	return  string_format("%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
					a, z, nu, eta, s, sz, st, T_err, likelihood_avg(100));
}

>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
