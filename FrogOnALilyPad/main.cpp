#include <fstream>
#include <iostream>
#include <vector>

using uint8 = unsigned short;
using uint32 = unsigned int; 
using uint64 = unsigned long long;
using int64 = long long;

const int64 MIN_INT_64 = -9223372036854775807LL; 

int64 dp[1000];

int64 max(int64 a, int64 b) {
	return a > b ? a : b;
}

int64 solve(const uint32& begin_position, std::vector<uint32>& mosquitos_on_lilypad) {
	if(begin_position == mosquitos_on_lilypad.size() - 1) {
		return mosquitos_on_lilypad[begin_position];
	} else if(begin_position + 2 > mosquitos_on_lilypad.size() - 1) {
		return -1;
	} 
	if(dp[begin_position] != MIN_INT_64) {
		return dp[begin_position];
	}
	dp[begin_position]= max(solve(begin_position + 3, mosquitos_on_lilypad), solve(begin_position + 2, mosquitos_on_lilypad));
	if(dp[begin_position] == -1) {
		return dp[begin_position];
	} else {
		dp[begin_position] += mosquitos_on_lilypad[begin_position];
		return dp[begin_position];
	}
}

int main() {
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	
	uint32 lilypads_amount;
	input >> lilypads_amount;

	for(uint32 i = 0; i < lilypads_amount; ++i) {
		dp[i] = MIN_INT_64;
	}

	std::vector<uint32> mosquitos_on_lilypad(lilypads_amount);

	for(uint32 i = 0; i < lilypads_amount; ++i) {
		input >> mosquitos_on_lilypad[i];
	}

	output << solve(0, mosquitos_on_lilypad);

	return 0;
}
