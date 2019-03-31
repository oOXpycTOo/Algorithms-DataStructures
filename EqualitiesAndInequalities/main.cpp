#include <fstream>
#include <string>
#include <vector>
#include <utility>

using uint8 = unsigned short;
using int8 = short;
using uint32 = unsigned long; 
using int32 = long;
using uint64 = unsigned long long;
using int64 = long long;

const int64 MIN_INT_64 = -9223372036854775807LL; 



class DisjointSetUnion {
	std::vector<int32> parent;
	std::vector<int32> rank;
	std::vector<bool> is_marked;
public:
	DisjointSetUnion(uint32 size) : parent(size), rank(size), is_marked(size) {}
	void make_set(int32 value) {
		parent[value] = value;
		rank[value] = 0;
		is_marked[value] = true;
	}

	int32 find(int32 value) {
		return value == parent[value] ? value : parent[value] = find(parent[value]);
	}

	bool is_value_marked(int32 value) {
		return is_marked[value];
	}

	void union_sets(int value_1, int value_2) {
		if((value_1 = find(value_1)) == (value_2 = find(value_2))) {
			return;				
		}
		if(rank[value_1] < rank[value_2]) {
			parent[value_1] = value_2;
		} else {
			parent[value_2] = value_1;
			if(rank[value_1] == rank[value_2]) {
				++rank[value_1];
			}
		}
	}
};

int main() {
	std::ifstream input("equal-not-equal.in");
	std::ofstream output("equal-not-equal.out");
	uint32 variables_amount, contraints_amount;
	input >> variables_amount>> contraints_amount;
	int32 x_i, x_j;
	std::string temp, sign;
	DisjointSetUnion equal_classes(variables_amount + 1);
	std::vector<std::pair<int32, int32>> not_equal;
	for(uint32 i = 0; i < contraints_amount; ++i) {
		input >> temp;
		x_i = std::stoi(temp.substr(1));
		input >> sign;
		input >> temp;
		x_j = std::stoi(temp.substr(1));
		if(sign == "==") {
			if(!(equal_classes.is_value_marked(x_i) || equal_classes.is_value_marked(x_j))) {
				equal_classes.make_set(x_i);
				if(x_i != x_j) {
					equal_classes.make_set(x_j);
					equal_classes.union_sets(x_i, x_j);
				}

			} else if(equal_classes.is_value_marked(x_i) && equal_classes.is_value_marked(x_j)) {
				if(equal_classes.find(x_i) != equal_classes.find(x_j)) {
					equal_classes.union_sets(x_i, x_j);
				}
			} else if(equal_classes.is_value_marked(x_i)) {
				equal_classes.make_set(x_j);
				equal_classes.union_sets(x_i, x_j);
			} else if(equal_classes.is_value_marked(x_j)) {
				equal_classes.make_set(x_i);
				equal_classes.union_sets(x_j, x_i);
			}
		} else {
			if(x_i == x_j) {
				output << "No";
				return 0;
			}
			not_equal.push_back(std::make_pair(x_i, x_j));
		}
	}
	for(auto expression : not_equal) {
		if(equal_classes.is_value_marked(expression.first) && equal_classes.is_value_marked(expression.second)) {
			if(equal_classes.find(expression.first) == equal_classes.find(expression.second)) {
				output << "No";
				return 0;
			}
		}
	}
	output << "Yes";
	return 0;
}
