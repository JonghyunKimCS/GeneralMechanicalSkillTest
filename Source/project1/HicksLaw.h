<<<<<<< HEAD
#pragma once

#ifndef HC_L
#define HC_L

#include "dependencies.h"
using namespace std;

/* Class FittsLaw implemented the Hick's Law.
 * Your input file must be .csv extension with three columns:
 * [N][RT (ms)]
 * without headers.
 *
 * RESULT FORM:
 * [a (intercept)][b][R^2]
 */

namespace HC
{
	struct DATA
	{
		float N;
		float RT;
	};
}

class HicksLaw
{
private:
	float a, b;

	string data_fn;
	vector<HC::DATA> input_data;

public:
	HicksLaw() : a(0.0f), b(1.0f) {}
	void set_param(float _a, float _b);
	void debug_print_param(bool data_flag);
	void load_data(HC::DATA d);
	float predict(HC::DATA d);
	float COD();
	void clear();
	void linear_regression();
	string result_header();
	string result_csv_form();
};

#endif HC_L
=======
#pragma once

#ifndef HC_L
#define HC_L

#include "dependencies.h"
using namespace std;

/* Class FittsLaw implemented the Hick's Law.
 * Your input file must be .csv extension with three columns:
 * [N][RT (ms)]
 * without headers.
 *
 * RESULT FORM:
 * [a (intercept)][b][R^2]
 */

namespace HC
{
	struct DATA
	{
		float N;
		float RT;
	};
}

class HicksLaw
{
private:
	float a, b;

	string data_fn;
	vector<HC::DATA> input_data;

public:
	HicksLaw() : a(0.0f), b(1.0f) {}
	void set_param(float _a, float _b);
	void debug_print_param(bool data_flag);
	void load_data(HC::DATA d);
	float predict(HC::DATA d);
	float COD();
	void clear();
	void linear_regression();
	string result_header();
	string result_csv_form();
};

#endif HC_L
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
