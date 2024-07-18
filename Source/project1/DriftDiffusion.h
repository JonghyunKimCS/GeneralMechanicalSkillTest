<<<<<<< HEAD
#pragma once

#ifndef DR_DF
#define DR_DF

#include "dependencies.h"

using namespace std;

/* Class DriftDiffusion implemented the drift diffusion model.
 * Your input file must be .csv extension with two columns:
 * [Reaction time (float)][Correction flag (bool)]
 * without headers.
 * 
 * RESULT FORM:
 * [a][z][nu][eta][s][sz][st][T_err]
 */

#define MINIMAL_NUM_OF_INTER_TRIAL 2500
#define NUM_OF_LL_AVG_TRIAL 1

namespace DD
{
	struct DATA
	{
		float RT;	// Reaction Time
		float COR;	// Correction Flag
	};
}

class DriftDiffusion
{
private:
	float a, nu, eta, sz, st, z, T_err;
	float s = 0.1f;
	float step_size = 0.00005f;
	float dt = 0.01f;



	vector<float> rt_cor;	// List of RT on Correct cases
	vector<float> rt_err;	// List of RT on Error cases

	string data_fn;
	vector<DD::DATA> input_data;	// Input data

public:
	DriftDiffusion() : a(0.059f), nu(0.2378f), eta(0.1067f), sz(0.0321f), st(0.0943f), z(0.0295f), T_err(0.15f) {}
	void set_param(float _a, float _nu, float _eta, float _sz, float _st, float _T_err);
	void debug_print_param(bool data_flag);
	void load_data(DD::DATA d);
	void clear();
	float likelihood();
	float likelihood_avg(int N);
	string result_header();
	string result_csv_form();
};


=======
#pragma once

#ifndef DR_DF
#define DR_DF

#include "dependencies.h"

using namespace std;

/* Class DriftDiffusion implemented the drift diffusion model.
 * Your input file must be .csv extension with two columns:
 * [Reaction time (float)][Correction flag (bool)]
 * without headers.
 * 
 * RESULT FORM:
 * [a][z][nu][eta][s][sz][st][T_err]
 */

#define MINIMAL_NUM_OF_INTER_TRIAL 2500
#define NUM_OF_LL_AVG_TRIAL 1

namespace DD
{
	struct DATA
	{
		float RT;	// Reaction Time
		float COR;	// Correction Flag
	};
}

class DriftDiffusion
{
private:
	float a, nu, eta, sz, st, z, T_err;
	float s = 0.1f;
	float step_size = 0.00005f;
	float dt = 0.01f;



	vector<float> rt_cor;	// List of RT on Correct cases
	vector<float> rt_err;	// List of RT on Error cases

	string data_fn;
	vector<DD::DATA> input_data;	// Input data

public:
	DriftDiffusion() : a(0.059f), nu(0.2378f), eta(0.1067f), sz(0.0321f), st(0.0943f), z(0.0295f), T_err(0.15f) {}
	void set_param(float _a, float _nu, float _eta, float _sz, float _st, float _T_err);
	void debug_print_param(bool data_flag);
	void load_data(DD::DATA d);
	void clear();
	float likelihood();
	float likelihood_avg(int N);
	string result_header();
	string result_csv_form();
};


>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
#endif DR_DF