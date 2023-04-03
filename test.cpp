#include "matrix.hpp"
#include <iostream>

using line = std::array<int, 3>;

int main() {
    matrix<int, 3> m = {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    for (auto arr : m.m_buffer) {
        for (int n : arr) {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }
    std::cout << m.at({0, 0}) << std::endl;
    std::cout << m.at({2, 3}) << std::endl; // throws error nice :)

    return 0;
}
