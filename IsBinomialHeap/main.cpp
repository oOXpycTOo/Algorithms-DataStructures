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
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	uint32 size;
	input >> size;
	std::vector<int64> nodes(size + 1);
	for(uint32 i = 1; i < size + 1; ++i) {
		input >> nodes[i];
	}	
	std::string result = "Yes";
	for(uint32 i = 1; 2*i < size + 1; ++i) {
		if(2*i < size) {
			if(nodes[i] > nodes[2*i] || nodes[i] > nodes[2*i + 1]) {
				result = "No";
				break;
			}
		} else {
			if(nodes[i] > nodes[2*i]) {
				result = "No";
				break;
			} 
		}
	}
	if((size + 1) % 2 == 1) {
		if(nodes[size / 2] > nodes[size]) {
			result = "No";
		}
	}
	
	output << result; 

	return 0;
}
