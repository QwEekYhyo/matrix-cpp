#include "matrix.hpp"
#include <iostream>

using line = std::array<int, 3>;

int main() {
    matrix<int, 3> orig = {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    matrix<int, 3> m = orig;
    matrix<int, 3> addition = orig + m;
    addition = addition * -2;
    for (auto arr : addition.m_buffer) {
        for (int n : arr) {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }
    std::cout << m.at({0, 0}) << std::endl;

    return 0;
}
