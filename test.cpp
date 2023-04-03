#include "matrix.hpp"
#include <iostream>

using line = std::array<int, 3>;

int main() {
    matrix<int, 3> m = std::array<line, 3>{line{1, 2, 3}, line{4, 5, 6}, line{7, 8, 9}};
    for (auto arr : m.m_buffer) {
        for (int n : arr) {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }

    return 0;
}
