<<<<<<< HEAD
#pragma once

#ifndef FT_L
#define FT_L

#include "dependencies.h"
using namespace std;

/* Class FittsLaw implemented the Fitts' Law.
 * Your input file must be .csv extension with three columns:
 * [W][D][RT (ms)]
 * without headers.
 *
 * RESULT FORM:
 * [a (intercept)][b][R^2]
 */

namespace FT
{
	struct DATA
	{
		float ID;
		float MT;
	};
}

class FittsLaw
{
private:
	float a, b;

	string data_fn;
	vector<FT::DATA> input_data;

public:
	FittsLaw() : a(0.0f), b(1.0f) {}
	void set_param(float _a, float _b);
	void debug_print_param(bool data_flag);
	void load_data(FT::DATA d);
	void clear();
	float predict(FT::DATA d);
	float COD();
	void linear_regression();
	string result_header();
	string result_csv_form();
};

=======
#pragma once

#ifndef FT_L
#define FT_L

#include "dependencies.h"
using namespace std;

/* Class FittsLaw implemented the Fitts' Law.
 * Your input file must be .csv extension with three columns:
 * [W][D][RT (ms)]
 * without headers.
 *
 * RESULT FORM:
 * [a (intercept)][b][R^2]
 */

namespace FT
{
	struct DATA
	{
		float ID;
		float MT;
	};
}

class FittsLaw
{
private:
	float a, b;

	string data_fn;
	vector<FT::DATA> input_data;

public:
	FittsLaw() : a(0.0f), b(1.0f) {}
	void set_param(float _a, float _b);
	void debug_print_param(bool data_flag);
	void load_data(FT::DATA d);
	void clear();
	float predict(FT::DATA d);
	float COD();
	void linear_regression();
	string result_header();
	string result_csv_form();
};

>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
#endif FT_L