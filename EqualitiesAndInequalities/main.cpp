#include <fstream>
#include <stack>
#include <string>
#include <vector>

using uint8 = unsigned short;
using uint32 = unsigned int; 
using uint64 = unsigned long long;
using int64 = long long;

const int64 MIN_INT_64 = -9223372036854775807LL; 

struct Variable {
	bool value;
	std::vector<uint32> equal_to;
	std::vector<uint32> not_equal_to;
};

int main() {
	std::ifstream input("equal-not-equal.in");
	std::ofstream output("equal-not-equal.out");
	
	uint32 variables_amount;
	uint32 constraints_amount;
	input >> variables_amount >> constraints_amount;
	std::vector<Variable> variables(variables_amount + 1);
	std::vector<uint32> priorities(variables_amount + 1, -1);
	uint32 max_priority = 0;
	std::string expression;
	uint32 x_i;
	uint32 x_j;
	std::string sign;
	std::string result = "Yes";
	input >> expression;
	x_i = std::stoi(expression.substr(1));
	input >> sign;
	input >> expression;
	x_j = std::stoi(expression.substr(1));
	priorities[max_priority++] = x_i;
	if(x_i != x_j) {
		priorities[max_priority++] = x_j; 
	}
	if(sign == "==") {
		variables[x_i].equal_to.push_back(x_j);
	} else {
		variables[x_i].not_equal_to.push_back(x_j);
	}
	for(uint32 i = 0; i < constraints_amount; ++i) {
		input >> expression;
		x_i = std::stoi(expression.substr(1));
		input >> sign;
		input >> expression;
		x_j = std::stoi(expression.substr(1));
		if(sign == "==") {
			variables[x_i].equal_to.push(x_j);  
		} else {
			variables[x_i].not_equal_to.push(x_j);
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
