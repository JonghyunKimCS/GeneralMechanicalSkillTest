<<<<<<< HEAD
#pragma once

#ifndef OPTIM
#define OPTIM

//#include "DriftDiffusion.h"
//#include "MovingTargetSelection.h"
#include "FittsLaw.h"
using namespace cppOpt;

//static DriftDiffusion D;
//static MovingTargetSelection M;
static FittsLaw F;
/*
namespace DRIFT_DIFFUSION_MODEL
{
	float score(float _a, float _nu, float _eta, float _sz, float _st)
	{
		D.set_param(_a, _nu, _eta, _sz, _st);
		return D.likelihood_avg(1);
	}

	string runOptimizer()
	{
		
		// Prepare output file
		/*
		ofstream output_file;
		output_file.open(output_fn, std::ios::out | std::ios::binary);
		output_file << D.result_header();
		
		// Set Optimizer
		
		auto toOptimize = [](OptCalculation<float>& optCalculation)
		{
			optCalculation.result = score(optCalculation.get_parameter("a"),
										optCalculation.get_parameter("nu"),
										optCalculation.get_parameter("eta"),
										optCalculation.get_parameter("sz"),
										optCalculation.get_parameter("st"));

			//cout << optCalculation.to_string_values() << "=>\t" << optCalculation.result << endl;
		};
		
		OptBoundaries<float> optBoundaries;
		optBoundaries.add_boundary({ 0.05f, 0.2f, "a" });
		optBoundaries.add_boundary({ 0.05f, 0.4f, "nu" });
		optBoundaries.add_boundary({ 0.05f, 0.2f, "eta" });
		optBoundaries.add_boundary({ 0.01f, 0.15f, "sz" });
		optBoundaries.add_boundary({ 0.001f, 0.25f, "st" });

		unsigned int maxCalculations = 250;
		float coolingFactor = 0.95f;
		float startChance = 0.25f;

		OptTarget optTarget = OptTarget::MINIMIZE;

		// For each data file, run fitting and store it
		//for (const auto& input_file : input_list)
		//{

		
		//cout << "Loading data: " << input_file << endl;

		//D.load_data(input_file);

		OptCoordinator<float, false> coordinator(
			maxCalculations,
			toOptimize,
			optTarget,
			0);

		coordinator.add_child(make_unique<OptSimulatedAnnealing<float>>(
			optBoundaries,
			coolingFactor,
			startChance));

		coordinator.run_optimisation();


		// Record ... 

		
		
		
		return D.result_csv_form();
		

	}
}
*/
/*
namespace MOVING_TARGET_SELECTION
{
	float score(float _c1, float _c2, float _c3, float _c4, float _c5)
	{
		M.set_param(_c1, _c2, _c3, _c4, _c5);
		return M.LSQ();
	}

	void runOptimizer(vector<string> input_list, string output_fn)
	{
		cout << "Running Optimization Module : " << endl;
		cout << "---- Moving Target Selection ----" << endl;

		// Prepare output file
		ofstream output_file;
		output_file.open(output_fn, std::ios::out | std::ios::binary);
		output_file << M.result_header();

		// Set Optimizer
		auto toOptimize = [](OptCalculation<float>& optCalculation)
		{
			optCalculation.result = score(optCalculation.get_parameter("c1"),
										optCalculation.get_parameter("c2"),
										optCalculation.get_parameter("c3"),
										optCalculation.get_parameter("c4"),
										optCalculation.get_parameter("c5"));

			cout << optCalculation.to_string_values() << "=>\t" << optCalculation.result << endl;
		};

		OptBoundaries<float> optBoundaries;
		optBoundaries.add_boundary({ -0.5f, 0.5f, "c1" });
		optBoundaries.add_boundary({ 0.0f, 0.5f, "c2" });
		optBoundaries.add_boundary({ 0.0f, 0.1f, "c3" });
		optBoundaries.add_boundary({ 150.0f, 350.0f, "c4" });
		optBoundaries.add_boundary({ 0.0f, 2.0f, "c5" });

		unsigned int maxCalculations = 300;
		float coolingFactor = 0.95f;
		float startChance = 0.25f;

		OptTarget optTarget = OptTarget::MINIMIZE;

		// For each data file, run fitting and store it
		for (const auto& input_file : input_list)
		{
			cout << "Loading data: " << input_file << endl;

			M.load_data(input_file);

			OptCoordinator<float, false> coordinator(
				maxCalculations,
				toOptimize,
				optTarget,
				0);

			coordinator.add_child(make_unique<OptSimulatedAnnealing<float>>(
				optBoundaries,
				coolingFactor,
				startChance));

			coordinator.run_optimisation();

			cout << "Optimization Done!\n" << endl;

			// Record ... 
			output_file << M.result_csv_form();
		}

		output_file.close();
	}

}
*/
namespace FITTS_LAW
{
	string runOptimizer()
	{
			
		F.linear_regression();

		// Record ... 
		//output_file << F.result_csv_form();
		return F.result_csv_form();

	}
}

=======
#pragma once

#ifndef OPTIM
#define OPTIM

//#include "DriftDiffusion.h"
//#include "MovingTargetSelection.h"
#include "FittsLaw.h"
using namespace cppOpt;

//static DriftDiffusion D;
//static MovingTargetSelection M;
static FittsLaw F;
/*
namespace DRIFT_DIFFUSION_MODEL
{
	float score(float _a, float _nu, float _eta, float _sz, float _st)
	{
		D.set_param(_a, _nu, _eta, _sz, _st);
		return D.likelihood_avg(1);
	}

	string runOptimizer()
	{
		
		// Prepare output file
		/*
		ofstream output_file;
		output_file.open(output_fn, std::ios::out | std::ios::binary);
		output_file << D.result_header();
		
		// Set Optimizer
		
		auto toOptimize = [](OptCalculation<float>& optCalculation)
		{
			optCalculation.result = score(optCalculation.get_parameter("a"),
										optCalculation.get_parameter("nu"),
										optCalculation.get_parameter("eta"),
										optCalculation.get_parameter("sz"),
										optCalculation.get_parameter("st"));

			//cout << optCalculation.to_string_values() << "=>\t" << optCalculation.result << endl;
		};
		
		OptBoundaries<float> optBoundaries;
		optBoundaries.add_boundary({ 0.05f, 0.2f, "a" });
		optBoundaries.add_boundary({ 0.05f, 0.4f, "nu" });
		optBoundaries.add_boundary({ 0.05f, 0.2f, "eta" });
		optBoundaries.add_boundary({ 0.01f, 0.15f, "sz" });
		optBoundaries.add_boundary({ 0.001f, 0.25f, "st" });

		unsigned int maxCalculations = 250;
		float coolingFactor = 0.95f;
		float startChance = 0.25f;

		OptTarget optTarget = OptTarget::MINIMIZE;

		// For each data file, run fitting and store it
		//for (const auto& input_file : input_list)
		//{

		
		//cout << "Loading data: " << input_file << endl;

		//D.load_data(input_file);

		OptCoordinator<float, false> coordinator(
			maxCalculations,
			toOptimize,
			optTarget,
			0);

		coordinator.add_child(make_unique<OptSimulatedAnnealing<float>>(
			optBoundaries,
			coolingFactor,
			startChance));

		coordinator.run_optimisation();


		// Record ... 

		
		
		
		return D.result_csv_form();
		

	}
}
*/
/*
namespace MOVING_TARGET_SELECTION
{
	float score(float _c1, float _c2, float _c3, float _c4, float _c5)
	{
		M.set_param(_c1, _c2, _c3, _c4, _c5);
		return M.LSQ();
	}

	void runOptimizer(vector<string> input_list, string output_fn)
	{
		cout << "Running Optimization Module : " << endl;
		cout << "---- Moving Target Selection ----" << endl;

		// Prepare output file
		ofstream output_file;
		output_file.open(output_fn, std::ios::out | std::ios::binary);
		output_file << M.result_header();

		// Set Optimizer
		auto toOptimize = [](OptCalculation<float>& optCalculation)
		{
			optCalculation.result = score(optCalculation.get_parameter("c1"),
										optCalculation.get_parameter("c2"),
										optCalculation.get_parameter("c3"),
										optCalculation.get_parameter("c4"),
										optCalculation.get_parameter("c5"));

			cout << optCalculation.to_string_values() << "=>\t" << optCalculation.result << endl;
		};

		OptBoundaries<float> optBoundaries;
		optBoundaries.add_boundary({ -0.5f, 0.5f, "c1" });
		optBoundaries.add_boundary({ 0.0f, 0.5f, "c2" });
		optBoundaries.add_boundary({ 0.0f, 0.1f, "c3" });
		optBoundaries.add_boundary({ 150.0f, 350.0f, "c4" });
		optBoundaries.add_boundary({ 0.0f, 2.0f, "c5" });

		unsigned int maxCalculations = 300;
		float coolingFactor = 0.95f;
		float startChance = 0.25f;

		OptTarget optTarget = OptTarget::MINIMIZE;

		// For each data file, run fitting and store it
		for (const auto& input_file : input_list)
		{
			cout << "Loading data: " << input_file << endl;

			M.load_data(input_file);

			OptCoordinator<float, false> coordinator(
				maxCalculations,
				toOptimize,
				optTarget,
				0);

			coordinator.add_child(make_unique<OptSimulatedAnnealing<float>>(
				optBoundaries,
				coolingFactor,
				startChance));

			coordinator.run_optimisation();

			cout << "Optimization Done!\n" << endl;

			// Record ... 
			output_file << M.result_csv_form();
		}

		output_file.close();
	}

}
*/
namespace FITTS_LAW
{
	string runOptimizer()
	{
			
		F.linear_regression();

		// Record ... 
		//output_file << F.result_csv_form();
		return F.result_csv_form();

	}
}

>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
#endif OPTIM