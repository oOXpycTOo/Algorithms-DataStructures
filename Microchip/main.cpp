#include <iostream>
#include <fstream>
#include <vector>

class Point {
private:
    int x;
    int y;
public:
    Point(int x, int y);
    void calculate_distance(int field_size);
    friend std::istream& operator>>(std::istream& input, Point point);
};

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

std::istream& operator>>(std::istream& input, Point point) {
    input >> point.x >> point.y;
    return input;
}

int main() {
    std::vector<std::vector<bool>> occupied_positions;
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int a;
    int n;
    for(auto i = 0; i < a; ++i) {
        occupied_positions.push_back(std::vector<bool>(a));
    }
    for(auto i = 0; i < a; ++i) {
        for(auto j = 0; j < a; ++j) {
            std::cout << occupied_positions[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}