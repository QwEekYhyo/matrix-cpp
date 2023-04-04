#include <matrix.hpp>
#include <iostream>

using line = std::array<int, 3>;

int main() {
    matrix<int, 3> orig = {{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    matrix<int, 3> m = orig;
    matrix<int, 3> addition = orig + m;
    addition = addition * -2;
    addition = addition - orig;
    for (auto arr : addition.buffer()) {
        for (int n : arr) {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }
    std::cout << (addition != orig) << std::endl;
    matrix<int, 1, 3> row = {{69, 4, 3}};
    auto multiplication = row * orig;
    for (auto arr : multiplication.buffer()) {
        for (int n : arr) {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }

    return 0;
}
