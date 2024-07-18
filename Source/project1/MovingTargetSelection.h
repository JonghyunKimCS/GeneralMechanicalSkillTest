<<<<<<< HEAD
#pragma once

#ifndef MT_S
#define MT_S

#include "dependencies.h"
using namespace std;

/* Class DriftDiffusion implemented the drift diffusion model.
 * Your input file must be .csv extension with following format:
 * [p][t_zone][t_cue][s][r][ Responses ... (0 or 1) ]
 * without headers.
 *
 * RESULT FORM:
 * [c1 ... c4][R^2]
 */

namespace MTS
{
	struct DATA
	{
		float p;
		float t_zone;
		float t_cue;	
		float s;
		float r;
		float y;		// Observed Y
	};
}

class MovingTargetSelection
{
private:
	float c1, c2, c3, c4;
	string data_fn;
	vector<MTS::DATA> input_data;

public:
	MovingTargetSelection():c1(0.0f), c2(0.0f), c3(0.0f), c4(0.0f) {}
	void set_param(float _c1, float _c2, float _c3, float _c4);
	void debug_print_param(bool data_flag);
	void load_data(MTS::DATA d);
	float predict(MTS::DATA d);
	void clear();
	float LSQ();	// Sum of Lease Square
	float COD();	// Coeff. of det.
	string result_header();
	string result_csv_form();
};

=======
#pragma once

#ifndef MT_S
#define MT_S

#include "dependencies.h"
using namespace std;

/* Class DriftDiffusion implemented the drift diffusion model.
 * Your input file must be .csv extension with following format:
 * [p][t_zone][t_cue][s][r][ Responses ... (0 or 1) ]
 * without headers.
 *
 * RESULT FORM:
 * [c1 ... c4][R^2]
 */

namespace MTS
{
	struct DATA
	{
		float p;
		float t_zone;
		float t_cue;	
		float s;
		float r;
		float y;		// Observed Y
	};
}

class MovingTargetSelection
{
private:
	float c1, c2, c3, c4;
	string data_fn;
	vector<MTS::DATA> input_data;

public:
	MovingTargetSelection():c1(0.0f), c2(0.0f), c3(0.0f), c4(0.0f) {}
	void set_param(float _c1, float _c2, float _c3, float _c4);
	void debug_print_param(bool data_flag);
	void load_data(MTS::DATA d);
	float predict(MTS::DATA d);
	void clear();
	float LSQ();	// Sum of Lease Square
	float COD();	// Coeff. of det.
	string result_header();
	string result_csv_form();
};

>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
#endif MT_S