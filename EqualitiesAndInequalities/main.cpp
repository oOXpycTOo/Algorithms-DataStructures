#include <fstream>
#include <stack>
#include <string>
#include <vector>

using uint8 = unsigned short;
using int8 = short;
using uint32 = unsigned long; 
using int32 = long;
using uint64 = unsigned long long;
using int64 = long long;

const int64 MIN_INT_64 = -9223372036854775807LL; 

struct Variable {
	int8 value = -1;
	std::vector<uint32> equal_to;
	std::vector<uint32> not_equal_to;
	int32 priority = -1;
};

std::string is_system_solvable(std::vector<Variable>& variables, const std::vector<int32>& priorities) {
	for(const uint32& prior_variable_idx : priorities) {
		if(variables[prior_variable_idx].value == -1) {
			variables[prior_variable_idx].value = 1;
		}
		for(const uint32& variable_idx : variables[prior_variable_idx].equal_to) {
			if(variables[variable_idx].value == -1) {
				variables[variable_idx].value = variables[prior_variable_idx].value;				
			} else {
				if(variables[prior_variable_idx].value != variables[variable_idx].value) {
					return "No";	
				} 
			}
		}
		for(const uint32& variable_idx : variables[prior_variable_idx].not_equal_to) {
			if(variables[variable_idx].value == -1) {
				variables[variable_idx].value = variables[prior_variable_idx].value ^ 1;				
			} else {
				if(variables[prior_variable_idx].value == variables[variable_idx].value) {
					return "No";	
				}
			}
		}
	}
	return "Yes";
}

int main() {
	std::ifstream input("equal-not-equal.in");
	std::ofstream output("equal-not-equal.out");
	
	uint32 variables_amount;
	uint32 constraints_amount;
	input >> variables_amount >> constraints_amount;
	std::vector<Variable> variables(variables_amount + 1);
	std::string expression;
	uint32 x_i;
	uint32 x_j;
	std::string sign;
	input >> expression;
	x_i = std::stoi(expression.substr(1));
	input >> sign;
	input >> expression;
	x_j = std::stoi(expression.substr(1));
	std::vector<int32> priorities;
	priorities.push_back(x_i);
	variables[x_i].priority = priorities.size() - 1; 
	variables[x_i].value = 1;
	if(x_i != x_j) {
		priorities.push_back(x_j); 
		variables[x_j].priority = priorities.size() - 1; 
	}
	if(sign == "==") {
		variables[x_i].equal_to.push_back(x_j);
	} else {
		variables[x_i].not_equal_to.push_back(x_j);
	}
	for(uint32 i = 1; i < constraints_amount; ++i) {
		input >> expression;
		x_i = std::stoi(expression.substr(1));
		input >> sign;
		input >> expression;
		x_j = std::stoi(expression.substr(1));
		if(variables[x_i].priority != -1 && variables[x_j].priority != -1) {
			if(variables[x_i].priority <= variables[x_j].priority) {
				if(sign == "==") {
					variables[x_i].equal_to.push_back(x_j);
				} else {
					variables[x_i].not_equal_to.push_back(x_j);
				}
			} else {
				if(sign == "==") {
					variables[x_j].equal_to.push_back(x_i);
				} else {
					variables[x_j].not_equal_to.push_back(x_i);
				}
			}
		} else if(variables[x_i].priority == -1 && variables[x_j].priority == -1) {
			priorities.push_back(x_i);
			variables[x_i].priority = priorities.size() - 1;
			priorities.push_back(x_j);
			variables[x_j].priority = priorities.size() - 1; 
			if(sign == "==") {
				variables[x_i].equal_to.push_back(x_j);				
			} else {
				variables[x_i].not_equal_to.push_back(x_j);
			}
		} else if(variables[x_j].priority == -1) {
			priorities.push_back(x_j);
			variables[x_j].priority = priorities.size() - 1; 
			if(sign == "==") {
				variables[x_i].equal_to.push_back(x_j);
			} else {
				variables[x_i].not_equal_to.push_back(x_j);
			}
		} else if(variables[x_i].priority == -1) {
			priorities.push_back(x_i);
			variables[x_i].priority = priorities.size() - 1; 
			if(sign == "==") {
				variables[x_j].equal_to.push_back(x_i);
			} else {
				variables[x_j].not_equal_to.push_back(x_i);
			}
		} 
	}

	

	output << is_system_solvable(variables, priorities); 

	return 0;
}
