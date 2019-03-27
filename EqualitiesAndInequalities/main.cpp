#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using uint8 = unsigned short;
using uint32 = unsigned int; 
using uint64 = unsigned long long;
using int64 = long long;

const int64 MIN_INT_64 = -9223372036854775807LL; 

int main() {
	std::ifstream input("equal-not-equal.in");
	std::ofstream output("equal-not-equal.out");
	
	uint32 variables_amount;
	uint32 constraints_amount;
	input >> variables_amount >> constraints_amount;
	std::vector<bool> x(variables_amount + 1, false);
	std::vector<bool> not_x(variables_amount + 1, false);
	std::string expression;
	uint32 x_i;
	uint32 x_j;
	std::string sign;
	std::string result = "Yes";
	for(uint32 i = 0; i < constraints_amount; ++i) {
		input >> expression;
		x_i = std::stoi(expression.substr(1));
		input >> sign;
		input >> expression;
		x_j = std::stoi(expression.substr(1));
		if((!x[x_i] && !not_x[x_i] && !x[x_j] && !not_x[x_j])) {
			x[x_i] = true;
			if(sign == "==") {
				x[x_j] = true;
			} else {
				not_x[x_j] = true;
			}
		} else if(x[x_i]) {
			if(sign == "==") {
				x[x_j] = true;
			} else {
				not_x[x_j] = true;
			}
		} else if(x[x_j]) {
			if(sign == "==") {
				x[x_i] = true;
			} else {
				not_x[x_i] = true;
			}
		} else if(not_x[x_i]) {
			if(sign == "==") {
				not_x[x_j] = true;
			} else {
				x[x_j] = true;
			}
		} else {
			if(sign == "==") {
				not_x[x_i] = true;
			} else {
				x[x_i] = true;
			}
		}
	}

	for(uint32 i = 1; i < variables_amount + 1; ++i) {
		x[i] = x[i] & not_x[i];
		if(x[i]) {
			result = "No";
			break;
		}
	}

	output << result; 

	return 0;
}
