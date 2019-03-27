#include <iostream>
#include <fstream>
#include <vector>

using uint64 = unsigned long long;
using uint8 = unsigned short;

const uint64 MAX_UINT_64 = 18446744073709551615ULL;

uint64 dp[100][100];

uint64 calculate_weight(uint64 n, uint64 m, uint64 k) {
	return n * m * k;
}

uint64 solve(const std::vector<std::pair<uint8, uint8>>& matrix_params) {
	for(uint8 i = 0; i < matrix_params.size(); ++i) {
		dp[i][i] = 0;
	}
	uint64 inter_min_weight; 
	for(uint8 gap = 1; gap < matrix_params.size(); ++gap) {
		for(uint8 i = 0, j = i + gap; j < matrix_params.size(); ++i, ++j) {
			if(j == i + 1) { 
				dp[i][j] = calculate_weight(matrix_params[i].first, matrix_params[i].second, matrix_params[j].second);	
			} else {
				dp[i][j] = MAX_UINT_64;
				for(uint8 k = i; k < j; ++k) {
					inter_min_weight = 
						dp[i][k] +
					       	dp[k+1][j] + 
						calculate_weight(matrix_params[i].first, matrix_params[k+1].first, matrix_params[j].second);
					if(inter_min_weight < dp[i][j]) {
						dp[i][j] = inter_min_weight;
					}
				}
			}	
		}
	}
	return dp[0][matrix_params.size()-1];
}

int main() {
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	uint8 matrix_amount;
	input >> matrix_amount;
	std::vector<std::pair<uint8, uint8>> matrix_params(matrix_amount);
	for(uint8 i = 0; i < matrix_amount; ++i) {
		input >> matrix_params[i].first >> matrix_params[i].second;
	}
	output << solve(matrix_params);
}
