#include "OutputProcessor.h"
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>

namespace fs = std::filesystem;

void OutputProcessor::GetDimData(
	std::map<int, std::vector<double>>& basic,
	std::map<int, std::vector<double>>& msr,
	std::map<int, std::vector<double>>& psr,
	int dim_number) {


	for (const auto& entry : fs::directory_iterator(dir_path))
	{
		auto path = entry.path();
		std::string filename = path.filename().string();
		std::string a;
		int d = -1;
		int f = -1;

		AssessFile(filename, a, d, f);
		std::cout << a << d << f << std::endl;

		if (d != 10) continue;

		auto res = GetLastRowOfFile(path);
		if (a == "M") {
			msr.emplace(f, res);
		}
		else if (a == "P") {
			psr.emplace(f, res);
		}
		else if (a == "b") {
			basic.emplace(f, res);
		}
	}
}

void OutputProcessor::AssessFile(std::string filename, std::string& algorithm_name, int& dim_count, int& function_number) {

	int pos_After = -1;
	if (filename.find(MSR_name) != std::string::npos) {
		algorithm_name = "M";
		pos_After = filename.find(MSR_name) + MSR_name.length();
	}
	else if (filename.find(PSR_name) != std::string::npos) {
		algorithm_name = "P";
		pos_After = filename.find(PSR_name) + PSR_name.length();
	}
	else if (filename.find(basic_algorithm_name) != std::string::npos) {
		algorithm_name = "b";
		pos_After = filename.find(basic_algorithm_name) + basic_algorithm_name.length();
	}

	int filename_len = filename.length();
	std::string s1(1, filename[filename_len - 6]);
	std::string s2(1, filename[filename_len - 5]);
	std::string dim = s1 + s2;

	if (dim == "30") {
		dim_count = 30;
	}
	else if (dim == "10") {
		dim_count = 10;
	}

	int pos2 = filename.find("_", pos_After);
	int pos3 = filename.find("_", pos2 + 1);
	std::string fun_name_str = filename.substr(pos2 + 1, pos3 - pos2 - 1);
	function_number = std::stoi(fun_name_str);
}

std::vector<double> OutputProcessor::GetLastRowOfFile(std::filesystem::path path) {

	std::ifstream infile(path);
	std::string line;
	std::vector<double> result;

	int lineCount = -1;

	while (std::getline(infile, line))
	{
		lineCount++;
		if (lineCount != 13) continue;

		std::istringstream iss(line);
		double a;
		while (iss >> a) {
			result.push_back(a);
		}
	}

	infile.close();
	return result;
}

void OutputProcessor::GetParameters(std::vector<double> input, double& best, double& worst, double& median, double& mean, double& stddev) {
	if (input.size() == 0) return;
	std::sort(input.begin(), input.end());
	best = input[0];
	worst = input[input.size() - 1];

	median = input.size() % 2 == 0 ? (input[input.size() / 2] + input[(input.size() / 2) - 1]) / 2 : input[input.size() / 2];

	mean = std::reduce(input.begin(), input.end()) / input.size();

	double sq_sum = std::inner_product(input.begin(), input.end(), input.begin(), 0.0);
	stddev = std::sqrt(sq_sum / input.size() - mean * mean);
}

void OutputProcessor::GetFunctionParametersTable(std::map<int, std::vector<double>> rawValues, std::string output_path) {
	std::ofstream ofile(output_path);

	for(auto pair : rawValues) {
		int func_number = pair.first;
		auto func_values = pair.second;
		double best, worst, median, mean, stdev;
		GetParameters(func_values, best, worst, median, mean, stdev);
		ofile << func_number << " & " << best << " & " << worst << " & " << median << " & " << mean << " & " << stdev << "\\\\\\hline" << "\n";
	}
}

void OutputProcessor::Parse10Dim(std::string dir_path) {
	std::map<int, std::vector<double>> basic_data;
	std::map<int, std::vector<double>> msr_data;
	std::map<int, std::vector<double>> psr_data;
	GetDimData(basic_data, msr_data, psr_data, 10);
	GetFunctionParametersTable(basic_data, dir_path + "\\basic10.txt");
	GetFunctionParametersTable(msr_data, dir_path + "\\msr10.txt");
	GetFunctionParametersTable(psr_data, dir_path + "\\psr10.txt");
}

void OutputProcessor::Parse30Dim(std::string dir_path) {
	std::map<int, std::vector<double>> basic_data;
	std::map<int, std::vector<double>> msr_data;
	std::map<int, std::vector<double>> psr_data;
	GetDimData(basic_data, msr_data, psr_data, 30);
	GetFunctionParametersTable(basic_data, dir_path + "\\basic30.txt");
	GetFunctionParametersTable(msr_data, dir_path + "\\msr30.txt");
	GetFunctionParametersTable(psr_data, dir_path + "\\psr30.txt");
}