#pragma once
#include <map>
#include <vector>
#include <string>
#include <filesystem>

class OutputProcessor {

	std::string dir_path = ".\\data";
	std::string basic_algorithm_name = "DE_rand_1_bin";
	std::string MSR_name = "DE_rand_1_bin_MSR";
	std::string PSR_name = "DE_rand_1_bin_PSR";

public:

	
	void Parse10Dim(std::string dir_path);
	void Parse30Dim(std::string dir_path);
	void GetDimData(std::map<int, std::vector<double>>& basic, std::map<int, std::vector<double>>& msr, std::map<int, std::vector<double>>& psr, int dim_number);
	
private:
	void AssessFile(std::string filename, std::string& algorithm_name, int& dim_count, int& function_number);
	std::vector<double> GetLastRowOfFile(std::filesystem::path path_name);
	void GetParameters(std::vector<double> input, double& best, double& worst, double& median, double& mean, double& stddev);
	void GetFunctionParametersTable(std::map<int, std::vector<double>> rawValues, std::string output_path);
};